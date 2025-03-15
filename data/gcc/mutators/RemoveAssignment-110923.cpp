#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveAssignment : public Mutator, public RecursiveASTVisitor<RemoveAssignment> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetAssignments.empty()) return false;

        // Apply mutation to the last found assignment
        return applyMutation();
    }

    bool VisitBinaryOperator(BinaryOperator *BO) {
        // Check if the operator is an assignment
        if (BO->getOpcode() == BO_Assign) {
            if (auto *LHS = dyn_cast<DeclRefExpr>(BO->getLHS()->IgnoreParenCasts())) {
                if (auto *VD = dyn_cast<VarDecl>(LHS->getDecl())) {
                    // Check if the variable is 'b'
                    // if (VD->getName() == "b") {
                        TargetAssignments.push_back(BO);
                    // }
                }
            }
        }
        return true;
    }

private:
    std::vector<BinaryOperator *> TargetAssignments;

    bool applyMutation() {
        // Select the last assignment found for simplification
        BinaryOperator *Assignment = randElement(TargetAssignments);    // TargetAssignments.back();

        // Get the source range of the assignment statement
        SourceRange Range = Assignment->getSourceRange();
        
        // Get the start and end locations of the assignment
        SourceLocation StartLoc = Range.getBegin();    // Start of the assignment
        SourceLocation EndLoc = Range.getEnd();        // End of the assignment

        // Get the next location after the assignment for proper removal
        SourceLocation AfterEndLoc = Lexer::getLocForEndOfToken(
            EndLoc, 0, getRewriter().getSourceMgr(), getASTContext().getLangOpts());

        // Remove the entire assignment statement
        getRewriter().RemoveText(SourceRange(StartLoc, AfterEndLoc));

        return true;
    }
};

// Register the mutator
static RegisterMutator<RemoveAssignment> M(
    "RemoveAssignment",
    "Removes assignments to the variable 'b' in the code.");