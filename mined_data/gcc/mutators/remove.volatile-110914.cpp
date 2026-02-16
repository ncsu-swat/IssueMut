#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveVolatileQualifier110914 : public Mutator, public RecursiveASTVisitor<RemoveVolatileQualifier110914> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (VolatileVarDecls.empty()) return false;

        // for (VarDecl *VD : VolatileVarDecls) {
        VarDecl *VD = randElement(VolatileVarDecls);
            // Get the full variable declaration text
            auto &SM = getRewriter().getSourceMgr();
            auto &LangOpts = getASTContext().getLangOpts();
            
            // Find and remove 'volatile' keyword
            std::string DeclText = getRewriter().getRewrittenText(VD->getSourceRange());
            size_t VolPos = DeclText.find("volatile");
            if (VolPos != std::string::npos) {
                SourceLocation VolLoc = VD->getBeginLoc().getLocWithOffset(VolPos);
                SourceLocation EndLoc = VolLoc.getLocWithOffset(8); // "volatile" length
                getRewriter().RemoveText(SourceRange(VolLoc, EndLoc));
            }

            // Process memcpy calls in the function body
            if (const FunctionDecl *FD = dyn_cast<FunctionDecl>(VD->getDeclContext())) {
                if (const Stmt *Body = FD->getBody()) {
                    TraverseStmt(const_cast<Stmt*>(Body));
                }
            }
        // }
        return true;
    }

    bool VisitCallExpr(CallExpr *Call) {
        // if (FunctionDecl *FD = Call->getDirectCallee()) {
        //     if (FD->getName() == "__builtin_memcpy") {
        if (Call->getNumArgs() == 0) return true;
                if (const CStyleCastExpr *Cast = dyn_cast<CStyleCastExpr>(Call->getArg(0))) {
                    // Remove "(void *)" cast
                    getRewriter().RemoveText(
                        SourceRange(
                            Cast->getLParenLoc(),
                            Cast->getRParenLoc()));
                }
        //     }
        // }
        return true;
    }

    bool VisitVarDecl(VarDecl *VD) {
        if (VD->getType().isVolatileQualified()) {
            VolatileVarDecls.push_back(VD);
        }
        return true;
    }

private:
    std::vector<VarDecl*> VolatileVarDecls;
};

static RegisterMutator<RemoveVolatileQualifier110914> M(
    "remove.volatile.110914",
    "Removes volatile qualifier from variable declarations and related casts.");
