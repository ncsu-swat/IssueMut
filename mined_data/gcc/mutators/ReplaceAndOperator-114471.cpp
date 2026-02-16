#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ReplaceAndOperator : public Mutator, public RecursiveASTVisitor<ReplaceAndOperator> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        return hasMutated;  // Return whether any mutations were made
    }

    bool VisitBinaryOperator(BinaryOperator *Op) {
        if (Op->getOpcode() == BO_LAnd) {
            // We're mutating && to &
            SourceLocation Loc = Op->getExprLoc();
            if (Loc.isValid()) {
                getRewriter().ReplaceText(Loc, 2, "&"); // Replace "&&" with "&"
                hasMutated = true; // Indicate that we've made a mutation
            }
        }
        return true; // Continue visiting
    }

private:
    bool hasMutated = false; // Keep track of whether any mutation has occurred
};

// Register the mutator
static RegisterMutator<ReplaceAndOperator> M(
    "ReplaceAndOperator",
    "Replaces '&&' with '&' in quantize function.");