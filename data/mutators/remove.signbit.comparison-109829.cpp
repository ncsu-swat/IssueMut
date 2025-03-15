#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveSignbitComparison : public Mutator, 
    public RecursiveASTVisitor<RemoveSignbitComparison> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        return Modified;
    }

    bool VisitBinaryOperator(BinaryOperator *BinOp) {
        if (BinOp->getOpcode() != BO_NE)
            return true;

        Expr *LHS = BinOp->getLHS()->IgnoreParenImpCasts();
        Expr *RHS = BinOp->getRHS()->IgnoreParenImpCasts();

        if (auto *Call = dyn_cast<CallExpr>(LHS)) {
            if (auto *FD = dyn_cast<FunctionDecl>(Call->getCalleeDecl())) {
                if (FD->getNameAsString() == "__builtin_signbit") {
                    if (auto *IL = dyn_cast<IntegerLiteral>(RHS)) {
                        if (IL->getValue() == 0) {
                            SourceLocation Start = BinOp->getOperatorLoc();
                            SourceLocation End = RHS->getEndLoc();
                            getRewriter().RemoveText(
                                SourceRange(Start, 
                                    Lexer::getLocForEndOfToken(End, 0, 
                                        getRewriter().getSourceMgr(),
                                        getASTContext().getLangOpts())));
                            Modified = true;
                        }
                    }
                }
            }
        }
        return true;
    }

private:
    bool Modified = false;
};

static RegisterMutator<RemoveSignbitComparison> X(
    "remove.signbit.comparison", 
    "Removes != 0 comparison with __builtin_signbit calls");