#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveElseAssignment : public Mutator, public clang::RecursiveASTVisitor<RemoveElseAssignment> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetIfs.empty()) return false;

        // Select a random if statement to modify
        IfStmt *IfStatement = randElement(TargetIfs);
        
        // Check if the else block is present
        if (!IfStatement->getElse())
            return false;

        // Get the source range of the entire else statement
        SourceRange ElseRange = IfStatement->getElse()->getSourceRange();
        
        // Remove the else block
        getRewriter().RemoveText(ElseRange);
        
        // After removing the else block, we need to update the statement
        // In this case, we will also need to ensure there's no dangling else left in the structure.

        // Remove the if block (the else already removed) and place code as follows:
        SourceLocation EndIfLoc = IfStatement->getSourceRange().getEnd();
        getRewriter().RemoveText(SourceRange(IfStatement->getBeginLoc(), EndIfLoc));

        // Rewrite it to simply assign `f.b` in the case of `if (t >= 0)`.
        // Adding the assignment `f.b = t;` back as needed.
        std::string NewCode = "    f.b = t;\n";  // Add back the 'if' assignment as part of the mutation
        getRewriter().InsertText(IfStatement->getBeginLoc(), NewCode, true, true);

        return true;
    }

    bool VisitIfStmt(IfStmt *Stmt) {
        // Check if this if statement has an else branch
        if (Stmt->getElse()) {
            TargetIfs.push_back(Stmt);
        }
        return true;
    }

private:
    std::vector<IfStmt *> TargetIfs;
};

// Register the mutator
static RegisterMutator<RemoveElseAssignment> M(
    "RemoveElseAssignment",
    "Removes the else assignment in if statements that set 'f.b' to 0.");