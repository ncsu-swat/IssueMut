#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RenameFunction : public Mutator, public clang::RecursiveASTVisitor<RenameFunction> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetFunctions.empty()) return false;

        // Select a random function declaration to modify
        FunctionDecl *FuncDecl = randElement(TargetFunctions);
        
        // Get the location of the function name
        SourceLocation NameLoc = FuncDecl->getLocation();
        if (NameLoc.isInvalid())
            return false;

        // Prepare the new name
        std::string NewName = "f";

        // Replace the function's name
        getRewriter().ReplaceText(NameLoc, FuncDecl->getName().size(), NewName);

        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *Decl) {
        // Check if the function is defined and not a built-in
        if (Decl->hasBody() && !Decl->isImplicit()/* && Decl->getName() == "g"*/) {
            TargetFunctions.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<FunctionDecl *> TargetFunctions;
};

// Register the mutator
static RegisterMutator<RenameFunction> M(
    "RenameFunction",
    "Renames the function 'g' to 'f'.");