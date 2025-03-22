#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveFunctionBody : public Mutator, public clang::RecursiveASTVisitor<RemoveFunctionBody> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetFunctions.empty()) return false;

        // Select a random function to modify
        FunctionDecl *FuncDecl = randElement(TargetFunctions);

        // Get the source location of the function body
        SourceLocation BodyStartLoc = FuncDecl->getBody()->getBeginLoc();
        SourceLocation BodyEndLoc = FuncDecl->getBody()->getEndLoc();

        // Remove the current function body
        getRewriter().RemoveText(SourceRange(BodyStartLoc, BodyEndLoc));

        // Insert an empty body after the function declaration
        SourceLocation InsertLoc = FuncDecl->getEndLoc();
        getRewriter().InsertTextAfter(InsertLoc, " {}");

        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *Decl) {
        // Check if the function has a body and is not a constructor/destructor
        if (Decl->hasBody() && !Decl->isImplicit()) {
            TargetFunctions.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<FunctionDecl *> TargetFunctions;
};

// Register the mutator
static RegisterMutator<RemoveFunctionBody> M(
    "RemoveFunctionBody",
    "Removes the body of a function and replaces it with an empty body.");