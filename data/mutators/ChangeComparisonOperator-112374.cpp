#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeComparisonOperator : public Mutator, public RecursiveASTVisitor<ChangeComparisonOperator> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetComparisons.empty())
            return false;

        // Select a random comparison to modify
        BinaryOperator *Comparison = randElement(TargetComparisons);
        
        // Get the location where the operator starts
        SourceLocation OperatorLoc = Comparison->getOperatorLoc();
        
        // Replace '>' with '>=' in the source code
        getRewriter().ReplaceText(OperatorLoc, 1, ">=");
        
        return true;
    }

    bool VisitBinaryOperator(BinaryOperator *Op) {
        // Check if the operator is '>'
        if (Op->getOpcode() == BO_GT) {
            // Store this operation for mutation
            TargetComparisons.push_back(Op);
        }
        return true;
    }

private:
    std::vector<BinaryOperator *> TargetComparisons;
};

// Register the mutator
static RegisterMutator<ChangeComparisonOperator> M(
    "ChangeComparisonOperator.gt",
    "Changes the comparison operator from '>' to '>='.");