#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

#include <random> // Include for random number generation

using namespace clang;

class CastCharTypeToForLoopIncrement : public Mutator, public RecursiveASTVisitor<CastCharTypeToForLoopIncrement> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetIncrements.empty()) return false;

        // Select a random increment expression to modify
        Expr *Inc = randElement(TargetIncrements);

        // Apply mutation to the selected increment expression
        // Get the source code location of the increment expression
        SourceLocation StartLoc = Inc->getBeginLoc();
        SourceLocation EndLoc = Inc->getEndLoc();
        
        if (StartLoc.isInvalid() || EndLoc.isInvalid())
            return false;

        // Get the variable being incremented
        if (const auto *UnaryOp = dyn_cast<UnaryOperator>(Inc)) {
            if (UnaryOp->isIncrementOp() && UnaryOp->isPostfix()) {
                if (const auto *DeclRef = dyn_cast<DeclRefExpr>(UnaryOp->getSubExpr())) {
                    std::string VarName = DeclRef->getNameInfo().getAsString();
                    // Construct the new increment expression
                    std::string NewExpr = VarName + " = (char)(" + VarName + " + 1)";
                    // Replace the old increment expression with the new one
                    getRewriter().ReplaceText(SourceRange(StartLoc, EndLoc), NewExpr);
                    return true; // Mutation applied
                }
            }
        }

        return false; // No mutation applied
    }

    bool VisitForStmt(ForStmt *ForLoop) {
        // Get the increment expression of the for loop
        Expr *IncExpr = ForLoop->getInc();
        if (!IncExpr)
            return true;

        // Check if the increment expression is a unary operator
        if (auto *UnaryOp = dyn_cast<UnaryOperator>(IncExpr)) {
            if (UnaryOp->isIncrementOp() && UnaryOp->isPostfix()) {
                // Add to the list of increments to potentially mutate
                TargetIncrements.push_back(IncExpr);
            }
        }

        return true;
    }

private:
    std::vector<Expr *> TargetIncrements;
};

// Register the mutator
static RegisterMutator<CastCharTypeToForLoopIncrement> M(
    "CastCharTypeToForLoopIncrement",
    "Mutates 'e++' in a randomly selected for-loop increment to 'e = (char)(e + 1)'.");