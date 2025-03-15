#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

// Utility function to select a random element from a vector
template <typename T>
T randElement(const std::vector<T> &vec) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, vec.size() - 1);
    return vec[dis(gen)];
}

class AlterLoopStructures : public Mutator, public RecursiveASTVisitor<AlterLoopStructures> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (ForLoops.empty()) return false;

        // Select a random loop to modify
        ForStmt *Loop = randElement(ForLoops);

        SourceLocation ForLoc = Loop->getForLoc();
        SourceLocation LParenLoc = Loop->getLParenLoc();
        SourceLocation RParenLoc = Loop->getRParenLoc();

        if (ForLoc.isInvalid() || LParenLoc.isInvalid() || RParenLoc.isInvalid())
            return false;

        // Build the new loop components
        std::string NewInit = ";";
        std::string NewCond = "";
        std::string NewInc = "";

        // Condition
        if (Expr *CondExpr = Loop->getCond()) {
            if (BinaryOperator *CondOp = dyn_cast<BinaryOperator>(CondExpr)) {
                if (DeclRefExpr *CondVar = dyn_cast<DeclRefExpr>(CondOp->getRHS()->IgnoreParenCasts())) {
                    NewCond = CondVar->getNameInfo().getAsString();
                } else if (IntegerLiteral *IntLit = dyn_cast<IntegerLiteral>(CondOp->getRHS())) {
                    // Use the integer literal directly
                    NewCond = IntLit->getValue().toString(10, false);
                }
            }
        }

        // Increment
        if (Expr *IncExpr = Loop->getInc()) {
            if (UnaryOperator *IncOp = dyn_cast<UnaryOperator>(IncExpr)) {
                if (DeclRefExpr *IncVar = dyn_cast<DeclRefExpr>(IncOp->getSubExpr()->IgnoreParenCasts())) {
                    NewInc = IncVar->getNameInfo().getAsString();
                }
            }
        }

        // Replace the loop header
        SourceLocation StartLoc = ForLoc;
        SourceLocation EndLoc = RParenLoc;
        EndLoc = Lexer::getLocForEndOfToken(
            EndLoc, 0, getRewriter().getSourceMgr(), getASTContext().getLangOpts());

        if (StartLoc.isInvalid() || EndLoc.isInvalid())
            return false;

        std::string NewForStmt = "for (" + NewInit + " " + NewCond + "; " + NewInc + ")";

        getRewriter().ReplaceText(SourceRange(StartLoc, EndLoc), NewForStmt);

        return true;
    }

    bool VisitForStmt(ForStmt *ForLoop) {
        // Collect all for-loops for potential mutation
        ForLoops.push_back(ForLoop);
        return true;
    }

private:
    std::vector<ForStmt *> ForLoops;
};

// Register the mutator
static RegisterMutator<AlterLoopStructures> M(
    "AlterLoopStructures",
    "Alters a randomly selected loop structure by removing initialization and increment.");