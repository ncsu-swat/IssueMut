#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeIfToTernaryOperator : public Mutator, public RecursiveASTVisitor<ChangeIfToTernaryOperator> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (IfStmts.empty())
            return false;

        // Select a random if-statement to modify
        IfStmt *ifStmt = randElement(IfStmts);

        // Ensure the 'if' statement has no 'else' part
        if (ifStmt->getElse())
            return false;

        // Get the condition expression
        Expr *condition = ifStmt->getCond();
        if (!condition)
            return false;

        // Get the 'then' statement
        Stmt *thenStmt = ifStmt->getThen();

        // Handle single-statement 'then' blocks
        if (CompoundStmt *compoundThen = dyn_cast<CompoundStmt>(thenStmt)) {
            if (compoundThen->size() == 1) {
                thenStmt = *(compoundThen->body_begin());
            } else {
                // We only handle single-statement 'then' blocks
                return false;
            }
        }

        // Check if 'thenStmt' is a compound assignment (e.g., '|=')
        if (BinaryOperator *binOp = dyn_cast<BinaryOperator>(thenStmt)) {
            if (binOp->isCompoundAssignmentOp()) {
                // Extract LHS and RHS
                Expr *lhs = binOp->getLHS();
                Expr *rhs = binOp->getRHS();

                // Get operator string
                std::string opStr = binOp->getOpcodeStr().str();

                // Build the new ternary expression
                std::string conditionStr = exprToString(condition);
                std::string lhsStr = exprToString(lhs);
                std::string rhsStr = exprToString(rhs);

                // For the example, we need to adjust the RHS inside the ternary
                // In the example, '3UL << (i * 2)' becomes '3' inside the ternary,
                // and the shift operation remains outside.

                // Attempt to split the RHS if it is a shift operation
                Expr *shiftBase = nullptr;
                Expr *shiftAmount = nullptr;
                if (BinaryOperator *rhsBinOp = dyn_cast<BinaryOperator>(rhs)) {
                    if (rhsBinOp->getOpcode() == BO_Shl) {
                        shiftBase = rhsBinOp->getLHS();
                        shiftAmount = rhsBinOp->getRHS();
                    }
                }

                std::string newExpr;
                if (shiftBase && shiftAmount) {
                    // Build the new expression with the shift outside the ternary
                    std::string shiftBaseStr = exprToString(shiftBase);
                    std::string shiftAmountStr = exprToString(shiftAmount);
                    newExpr = lhsStr + " " + opStr + " ((" + conditionStr + " ? " + shiftBaseStr + " : 0) << " + shiftAmountStr + ");";
                } else {
                    // General case
                    newExpr = lhsStr + " " + opStr + " (" + conditionStr + " ? " + rhsStr + " : 0);";
                }

                // Replace the 'if' statement with the new expression
                SourceRange ifRange = getFullStmtRange(ifStmt);
                getRewriter().ReplaceText(ifRange, newExpr);

                return true;
            }
        }

        return false;
    }

    bool VisitIfStmt(IfStmt *ifStmt) {
        // We collect 'if' statements without 'else' part
        if (!ifStmt->getElse()) {
            IfStmts.push_back(ifStmt);
        }
        return true;
    }

private:
    std::vector<IfStmt *> IfStmts;

    std::string exprToString(const Expr *expr) {
        SourceManager &SM = getSourceManager();
        LangOptions LangOpts = getASTContext().getLangOpts();
        LangOpts.Bool = true; // Ensure 'true'/'false' are printed as such

        SourceLocation startLoc = expr->getBeginLoc();
        SourceLocation endLoc = expr->getEndLoc();
        endLoc = Lexer::getLocForEndOfToken(endLoc, 0, SM, LangOpts);

        CharSourceRange charRange = CharSourceRange::getCharRange(startLoc, endLoc);
        return Lexer::getSourceText(charRange, SM, LangOpts).str();
    }

    SourceRange getFullStmtRange(const Stmt *stmt) {
        SourceManager &SM = getSourceManager();
        LangOptions LangOpts = getASTContext().getLangOpts();

        SourceLocation startLoc = stmt->getBeginLoc();
        SourceLocation endLoc = stmt->getEndLoc();
        endLoc = Lexer::getLocForEndOfToken(endLoc, 0, SM, LangOpts);

        return SourceRange(startLoc, endLoc);
    }
};

// Register the mutator
static RegisterMutator<ChangeIfToTernaryOperator> M(
    "ChangeIfToTernaryOperator",
    "Transforms specific if statements into ternary expressions."
);