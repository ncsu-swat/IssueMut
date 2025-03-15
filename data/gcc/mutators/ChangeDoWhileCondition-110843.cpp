#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeDoWhileCondition : public Mutator, public clang::RecursiveASTVisitor<ChangeDoWhileCondition> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetDoWhile.empty()) return false;

        // Select a random do-while statement to modify
        DoStmt *doWhileStmt = randElement(TargetDoWhile);
        
        // Get the source location for the while statement's condition
        Stmt *condition = doWhileStmt->getCond();
        if (!condition) return false;

        // Create a new condition
        // std::string NewCondition = "v32u64_0[0]"; // New condition

        // Get the location to insert the new condition
        SourceLocation StartLoc = condition->getBeginLoc();
        SourceLocation EndLoc = condition->getEndLoc();
        if (StartLoc.isInvalid() || EndLoc.isInvalid())
            return false;

        std::string ConditionString = getText(SourceRange(StartLoc, EndLoc));
        size_t pos = ConditionString.find(' ');

        // If a space is found, remove everything after it
        if (pos != std::string::npos) {
            ConditionString = ConditionString.substr(0, pos); // Keep only the part before the space
        }

        // Remove the old condition
        getRewriter().RemoveText(SourceRange(StartLoc, EndLoc));

        // Insert the new condition
        getRewriter().InsertText(StartLoc, ConditionString, true, true);

        return true;
    }

    bool VisitDoStmt(DoStmt *stmt) {
        // Collect all do-while statements for mutation
        if (stmt && stmt->getBody() && stmt->getCond()) {
            TargetDoWhile.push_back(stmt);
        }
        return true;
    }

private:
    std::vector<DoStmt *> TargetDoWhile;
    std::string getText(SourceRange Range) {
        return Lexer::getSourceText(
            CharSourceRange::getTokenRange(Range),
            getASTContext().getSourceManager(),
            getASTContext().getLangOpts()).str();
    }
};

// Register the mutator
static RegisterMutator<ChangeDoWhileCondition> M(
    "ChangeDoWhileCondition",
    "Changes the condition of randomly selected do-while statements.");