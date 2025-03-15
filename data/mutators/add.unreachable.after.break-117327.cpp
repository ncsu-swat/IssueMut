#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class AddUnreachableAfterBreak : public Mutator, 
    public RecursiveASTVisitor<AddUnreachableAfterBreak> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (BreakStmts.empty()) return false;

        // Select a random break statement
        BreakStmt *Target = randElement(BreakStmts);
        
        // Get source location after the break
        SourceLocation EndLoc = Target->getSourceRange().getEnd();
        SourceLocation InsertLoc = Lexer::getLocForEndOfToken(
            EndLoc, 0, getRewriter().getSourceMgr(), getASTContext().getLangOpts());
            
        if (InsertLoc.isInvalid())
            return false;

        // Insert unreachable check using same condition variable
        if (CondVar.empty()) return false;
        
        std::string NewCode = ";\n            if (" + CondVar + " == 7) __builtin_unreachable()";
        getRewriter().InsertTextAfter(InsertLoc, NewCode);

        return true;
    }

    bool VisitIfStmt(IfStmt *Stmt) {
        if (Stmt->getThen() && isa<BreakStmt>(Stmt->getThen())) {
            if (BinaryOperator *Cond = dyn_cast<BinaryOperator>(Stmt->getCond())) {
                if (Cond->getOpcode() == BO_EQ) {
                    // Get the condition variable
                    std::string Text = getText(Cond->getLHS());
                    if (!Text.empty()) {
                        CondVar = Text;
                    }
                }
            }
        }
        return true;
    }

    bool VisitBreakStmt(BreakStmt *Stmt) {
        BreakStmts.push_back(Stmt);
        return true;
    }

private:
    std::vector<BreakStmt*> BreakStmts;
    std::string CondVar;

    std::string getText(const Expr* E) {
        SourceRange Range = E->getSourceRange();
        return std::string(Lexer::getSourceText(
            CharSourceRange::getTokenRange(Range),
            getRewriter().getSourceMgr(),
            getASTContext().getLangOpts()));
    }
};

static RegisterMutator<AddUnreachableAfterBreak> M(
    "add.unreachable.after.break", 
    "Adds an unreachable condition after break statements.");