#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class DeleteCStyleCastInAVX : public Mutator, public RecursiveASTVisitor<DeleteCStyleCastInAVX> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (CastExprLocs.empty()) return false;
        
        // for (const auto &castLoc : CastExprLocs) {
        const auto &castLoc = randElement(CastExprLocs);
            getRewriter().RemoveText(castLoc);
        // }
        
        return true;
    }

    bool VisitCallExpr(CallExpr *Call) {
        if (FunctionDecl *FD = Call->getDirectCallee()) {
            StringRef Name = FD->getName();
            // if (Name.startswith("_mm") && 
            //     (Name.contains("srai") || Name.contains("srli") || Name.contains("slli"))) {
                if (Call->getNumArgs() > 0) {
                    for (unsigned i = 0; i < Call->getNumArgs(); i++) {
                        if (auto *Cast = dyn_cast<CStyleCastExpr>(Call->getArg(i))) {
                            SourceRange CastRange = Cast->getSourceRange();
                            SourceRange CastTypeRange(CastRange.getBegin(), 
                                Cast->getSubExprAsWritten()->getBeginLoc().getLocWithOffset(-1));
                            CastExprLocs.push_back(CastTypeRange);
                        }
                    }
                }
            // }
        }
        return true;
    }

private:
    std::vector<SourceRange> CastExprLocs;
};

static RegisterMutator<DeleteCStyleCastInAVX> M(
    "delete.cstylecast.avx", 
    "Removes C-style casts in AVX intrinsic function calls.");