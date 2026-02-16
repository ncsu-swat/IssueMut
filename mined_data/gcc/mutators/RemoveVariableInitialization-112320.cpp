#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveVariableInitialization112320 : public Mutator, public RecursiveASTVisitor<RemoveVariableInitialization112320> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        return !TargetVars.empty() && applyMutation();
    }

    bool VisitVarDecl(VarDecl *Decl) {
        // Check if it's a local variable, has an initializer, and is not static
        if (Decl->hasInit() && Decl->getParentFunctionOrMethod() && !Decl->isStaticLocal()) {
            TargetVars.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<VarDecl *> TargetVars;

    bool applyMutation() {
        // Select a random variable to mutate
        VarDecl *VarToMutate = randElement(TargetVars);

        // Get the location of the variable declaration
        SourceLocation DeclLoc = VarToMutate->getSourceRange().getBegin();

        // Get the location to insert the new code (before the initializer)
        SourceLocation InsertLoc = Lexer::getLocForEndOfToken(
            VarToMutate->getInit()->getSourceRange().getBegin(), -1, 
            getRewriter().getSourceMgr(), getASTContext().getLangOpts());
        if (InsertLoc.isInvalid())
            return false;

        // Create the new declaration string without the initializer
        std::string NewDecl = VarToMutate->getType().getAsString() + " " + VarToMutate->getName().str() + ";";
        
        // Remove the initializer
        getRewriter().RemoveText(VarToMutate->getInit()->getSourceRange());
        // Replace the variable declaration with the new declaration (no initializer)
        getRewriter().ReplaceText(DeclLoc, VarToMutate->getSourceRange().getEnd().printToString(getRewriter().getSourceMgr()).size(), NewDecl);
        
        return true;
    }
};

// Register the mutator
static RegisterMutator<RemoveVariableInitialization112320> M(
    "RemoveVariableInitialization",
    "Removes the initialization for a randomly selected local variable.");