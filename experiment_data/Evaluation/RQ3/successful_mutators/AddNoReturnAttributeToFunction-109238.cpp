#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class AddNoReturnAttributeToFunction : public Mutator, public clang::RecursiveASTVisitor<AddNoReturnAttributeToFunction> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseDecl(getASTContext().getTranslationUnitDecl());

        if (TargetFunctions.empty())
            return false;

        // Select a random function declaration to modify
        FunctionDecl *FD = randElement(TargetFunctions);

        // Check that FD is in the main file (not in a system header)
        if (getSourceManager().isInSystemHeader(FD->getLocation()))
            return false;

        // Get the TypeSourceInfo for the function declaration
        TypeSourceInfo *TSI = FD->getTypeSourceInfo();
        if (!TSI)
            return false;

        TypeLoc TL = TSI->getTypeLoc();
        if (TL.isNull())
            return false;

        // Get the FunctionTypeLoc to find the right parenthesis location
        FunctionTypeLoc FTL = TL.getAs<FunctionTypeLoc>();
        if (FTL.isNull())
            return false;

        // Get the location of the right parenthesis ')'
        SourceLocation RParenLoc = FTL.getRParenLoc();
        if (RParenLoc.isInvalid())
            return false;

        // Get the location after the right parenthesis to insert the attribute
        SourceLocation InsertLoc = Lexer::getLocForEndOfToken(
            RParenLoc, 0, getSourceManager(), getASTContext().getLangOpts());

        if (InsertLoc.isInvalid())
            return false;

        // Prepare the attribute text to insert
        std::string AttrText = " __attribute__((noreturn))";

        // Insert the attribute after the right parenthesis
        getRewriter().InsertText(InsertLoc, AttrText, /*InsertAfter=*/true);

        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *FD) {
        // Skip implicit functions and function definitions
        if (FD->isImplicit() || FD->isThisDeclarationADefinition())
            return true;

        // Add the function declaration to the list
        TargetFunctions.push_back(FD);
        return true;
    }

private:
    std::vector<FunctionDecl *> TargetFunctions;
};

// Register the mutator
static RegisterMutator<AddNoReturnAttributeToFunction> M(
    "AddNoReturnAttributeToFunction",
    "Adds '__attribute__((noreturn))' to a randomly selected function declaration.");