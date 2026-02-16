#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ModifyBuiltinMulOverflow : public Mutator, 
    public RecursiveASTVisitor<ModifyBuiltinMulOverflow> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (CallTargets.empty()) return false;

        CallExpr *Target = randElement(CallTargets);
        
        // Get location of the last argument's literal
        Expr *Arg3 = Target->getArg(2);
        
        // Replace the whole argument with "0"
        getRewriter().ReplaceText(
            SourceRange(Arg3->getBeginLoc(), Arg3->getEndLoc()),
            "0");

        // Add casts
        SourceLocation Arg1Start = Target->getArg(0)->getBeginLoc();
        getRewriter().InsertTextBefore(Arg1Start, "(unsigned _BitInt(1)) ");
        getRewriter().InsertTextBefore(Arg3->getBeginLoc(), "(_BitInt(33)) ");

        return true;
    }

    bool VisitCallExpr(CallExpr *E) {
        if (FunctionDecl *FD = E->getDirectCallee()) {
            if (FD->getNameAsString() == "__builtin_mul_overflow_p") {
                CallTargets.push_back(E);
            }
        }
        return true;
    }

private:
    std::vector<CallExpr *> CallTargets;
};

static RegisterMutator<ModifyBuiltinMulOverflow> M(
    "modify.builtin.mul.overflow",
    "Modifies __builtin_mul_overflow_p call by adding _BitInt casts to arguments");