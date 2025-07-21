#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveVolatileQualifier108692 : public Mutator, 
    public RecursiveASTVisitor<RemoveVolatileQualifier108692> {

public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (VolatileDecls.empty()) return false;

        // for (auto* VD : VolatileDecls) {
        auto* VD = randElement(VolatileDecls);
            SourceLocation VolLoc = VD->getBeginLoc();
            if (VolLoc.isValid()) {
                getRewriter().RemoveText(
                    SourceRange(VolLoc, 
                    Lexer::getLocForEndOfToken(VolLoc, 0, 
                        getRewriter().getSourceMgr(),
                        getASTContext().getLangOpts())));
            }
        // }
        return true;
    }

    bool VisitVarDecl(VarDecl *Decl) {
        if (Decl->getType().isVolatileQualified()) {
            VolatileDecls.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<VarDecl*> VolatileDecls;
};

static RegisterMutator<RemoveVolatileQualifier108692> M(
    "remove.volatile.108692", 
    "Removes volatile qualifier from variable declarations.");
