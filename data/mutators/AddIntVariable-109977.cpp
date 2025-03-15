#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class AddIntVariable : public Mutator, public RecursiveASTVisitor<AddIntVariable> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetFunctions.empty()) return false;

        // Select the first function declaration to modify (assuming we modify `foo`)
        FunctionDecl *FuncDecl = randElement(TargetFunctions); // TargetFunctions.front();
        
        // Get the location of the opening brace
        SourceLocation StartLoc = FuncDecl->getBody()->getBeginLoc();
        SourceLocation InsertLoc = Lexer::getLocForEndOfToken(
            StartLoc, -1, getRewriter().getSourceMgr(), getASTContext().getLangOpts());
        if (InsertLoc.isInvalid())
            return false;

        std::string NewVarDecl = "    int i;\n";
        getRewriter().InsertTextBefore(InsertLoc, NewVarDecl);

        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *Decl) {
        // Check if the declaration is the target function 'foo'
        // if (Decl->getName() == "foo") {
            TargetFunctions.push_back(Decl);
        // }
        return true;
    }

private:
    std::vector<FunctionDecl *> TargetFunctions;
};

// Register the mutator
static RegisterMutator<AddIntVariable> M(
    "AddIntVariable",
    "Adds an integer variable 'i' before the body of the function 'foo'.");