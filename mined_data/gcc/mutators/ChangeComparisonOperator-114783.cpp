#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeComparisonOperatorEq : public Mutator, public RecursiveASTVisitor<ChangeComparisonOperatorEq> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        return !TargetReturns.empty();
    }

    bool VisitBinaryOperator(BinaryOperator *Op) {
        // Check if it's a comparison operator for the specific case
        if (Op->getOpcode() == BO_NE) {
            TargetReturns.push_back(Op);
        }
        return true;
    }

    bool VisitReturnStmt(ReturnStmt *Ret) {
        // If we have a suitable return statement with the target operator
        if (const auto *Op = dyn_cast<BinaryOperator>(Ret->getRetValue())) {
            if (Op->getOpcode() == BO_NE) {
                SourceLocation OpLoc = Op->getOperatorLoc();
                
                // Replace the '!=' operator with '=='
                getRewriter().ReplaceText(OpLoc, 2, "==");
            }
        }
        return true;
    }

private:
    std::vector<BinaryOperator *> TargetReturns; // To store return statements to modify
};

// Register the mutator
static RegisterMutator<ChangeComparisonOperatorEq> M(
    "ChangeComparisonOperator.eq",
    "Changes '!=' to '==' in a return statement of a function.");