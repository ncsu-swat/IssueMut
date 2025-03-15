#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeInequalityToEquality : public Mutator, public clang::RecursiveASTVisitor<ChangeInequalityToEquality> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        return true;  // Return true to indicate we are trying to perform a mutation
    }

    bool VisitBinaryOperator(BinaryOperator *Op) {
        // Check if this is a binary operator and matches the specific case for '!='
        if (Op->getOpcode() == BO_NE) {
            // Get the source location for the operator for replacement
            SourceLocation OpLoc = Op->getOperatorLoc();
            // Prepare the replacement text
            std::string NewText = "==";
            // Insert the new text at the location of the existing operator
            getRewriter().ReplaceText(OpLoc, 2, NewText);
            return false; // Stop traversing deeper since we mutated this operator
        }
        return true; // Continue traversing if it's not mutated
    }
};

// Register the mutator
static RegisterMutator<ChangeInequalityToEquality> M(
    "ChangeInequalityToEquality",
    "Changes '!=' to '==' in function return statements.");