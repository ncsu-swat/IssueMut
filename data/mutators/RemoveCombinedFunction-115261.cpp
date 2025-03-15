#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveCombinedFunction : public Mutator, public clang::RecursiveASTVisitor<RemoveCombinedFunction> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        return !TargetFunctions.empty() && applyMutation();
    }

    bool VisitFunctionDecl(FunctionDecl *Decl) {
        // Look for 'combined_function' specifically
        // if (Decl->getName() == "combined_function") {
            TargetFunctions.push_back(Decl);
        // }
        return true;
    }

private:
    std::vector<FunctionDecl *> TargetFunctions;

    bool applyMutation() {
        // Select the target function to remove
        FunctionDecl *FunctionToRemove = randElement(TargetFunctions); //TargetFunctions.back();
        
        // Get the location of the function's body
        SourceLocation StartLoc = FunctionToRemove->getSourceRange().getBegin();
        SourceLocation EndLoc = FunctionToRemove->getSourceRange().getEnd();
        
        // Create a source manager reference
        SourceManager &SM = getRewriter().getSourceMgr();
        
        // Calculate the end location for removal (including the closing brace)
        SourceLocation AdjustedEndLoc = Lexer::getLocForEndOfToken(
            EndLoc, 0, SM, getASTContext().getLangOpts());

        if (StartLoc.isInvalid() || AdjustedEndLoc.isInvalid())
            return false;

        // Remove the entire function declaration and body
        getRewriter().RemoveText(SourceRange(StartLoc, AdjustedEndLoc));

        return true;
    }
};

// Register the mutator
static RegisterMutator<RemoveCombinedFunction> M(
    "RemoveCombinedFunction",
    "Removes the implementation of 'combined_function'.");