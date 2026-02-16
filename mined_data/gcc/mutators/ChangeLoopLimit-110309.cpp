#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeLoopIteratorLimit : public Mutator, public clang::RecursiveASTVisitor<ChangeLoopIteratorLimit> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        return !TargetLoops.empty() ? applyMutation() : false;
    }

    bool VisitForStmt(ForStmt *ForStatement) {
        // Find loop condition
        auto *Cond = ForStatement->getCond();

        // Check the loop condition to find the limit
        if (isLoopConditionEight(Cond)) {
            TargetLoops.push_back(ForStatement);
        }
        return true;
    }

private:
    std::vector<ForStmt*> TargetLoops;

    bool isLoopConditionEight(const Expr *Cond) {
        // Look for a comparison of the loop variable with 8
        if (auto *BinaryOp = dyn_cast<BinaryOperator>(Cond)) {
            if (BinaryOp->getOpcode() == BO_LT) { // check if it's a less than comparison
                if (auto *RHS = dyn_cast<IntegerLiteral>(BinaryOp->getRHS())) {
                    return RHS->getValue() != 6; // check if it's comparing against 8
                }
            }
        }
        return false;
    }

    bool applyMutation() {
        ForStmt *LoopStmt = randElement(TargetLoops); // TargetLoops.front();

        // Get the condition of the loop which needs modification
        auto *Cond = LoopStmt->getCond();
        
        // Ensure the condition is a binary operator of the form "i < 8"
        if (auto *BinaryOp = dyn_cast<BinaryOperator>(Cond)) {
            if (BinaryOp->getOpcode() == BO_LT) {
                // Get start of the right-hand side (the "8")
                SourceLocation RHSLoc = BinaryOp->getRHS()->getBeginLoc();

                // Get the length of the number to replace
                std::string CurrentValue = Lexer::getSourceText(CharSourceRange::getTokenRange(BinaryOp->getRHS()->getSourceRange()), 
                                                                getRewriter().getSourceMgr(), 
                                                                getASTContext().getLangOpts()).str();

                // Perform replacement from 8 to 6
                if (CurrentValue != "6") {
                    getRewriter().ReplaceText(RHSLoc, CurrentValue.length(), "6");
                    return true;
                }
            }
        }
        return false;
    }
};

// Register the mutator
static RegisterMutator<ChangeLoopIteratorLimit> M(
    "ChangeLoopLimit",
    "Changes loop condition from iterating 8 times to 6 times.");