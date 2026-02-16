#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class AddCastToVector : public Mutator, public clang::RecursiveASTVisitor<AddCastToVector> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        // Traverse the AST to find potential mutation targets
        TraverseAST(getASTContext());
        // Return success if mutations are made
        return true; // No need for a target check here as we mutate on each visit
    }

    bool VisitBinaryOperator(BinaryOperator *Op) {
        // Look for assignments
        if (Op->isAssignmentOp() && Op->getLHS()->getType()->isVectorType()) {
            // Fetch the source manager
            SourceManager &SM = getRewriter().getSourceMgr();

            // Get the current text of the right-hand side
            SourceRange RHSRange = Op->getRHS()->getSourceRange();
            std::string RHSText = Lexer::getSourceText(
                CharSourceRange::getTokenRange(RHSRange), SM, getASTContext().getLangOpts()).str();

            // Prepare the new text with casting
            std::string NewRHSText = "(V) " + RHSText;

            // Replace the RHS text in the original assignment
            getRewriter().ReplaceText(RHSRange, NewRHSText);
            return false; // Stop traversing further
        }
        return true; // Continue traversing the AST
    }
};

// Register the mutator
static RegisterMutator<AddCastToVector> M(
    "AddCastToVector",
    "Adds a cast to 'V' for the right-hand side of vector assignments.");