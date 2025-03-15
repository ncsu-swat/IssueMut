#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class IntroduceLoop : public Mutator, public clang::RecursiveASTVisitor<IntroduceLoop> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetFunctions.empty()) return false;

        // Select the main function for mutation
        FunctionDecl *MainFunc = TargetFunctions.front();

        // Get the location of the closing brace of the main function
        SourceLocation EndLoc = MainFunc->getSourceRange().getEnd();
        SourceLocation InsertLoc = Lexer::getLocForEndOfToken(
            EndLoc, 1, getRewriter().getSourceMgr(), getASTContext().getLangOpts());
        if (InsertLoc.isInvalid())
            return false;

        std::string NewLoop = "  for (long m = 0; m < 8; ++m)\n"
                              "    d = 1;\n";
        getRewriter().InsertTextBefore(InsertLoc, NewLoop);

        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *Decl) {
        // Check if the function name is "main"
        if (Decl->getNameInfo().getName().getAsString() == "main") {
            TargetFunctions.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<FunctionDecl *> TargetFunctions;
};

// Register the mutator
static RegisterMutator<IntroduceLoop> M(
    "IntroduceLoop",
    "Introduces a new loop in the main function that performs assignments on a variable.");