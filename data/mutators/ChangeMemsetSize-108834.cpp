#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeMemsetSize : public Mutator, public RecursiveASTVisitor<ChangeMemsetSize> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        return true; // Return true since mutations are applied during the visit
    }

    bool VisitCallExpr(CallExpr *Call) {
        // Check if it's a call to `memset`
        FunctionDecl *Callee = Call->getDirectCallee();
        if (Callee && Callee->getName() == "memset") {
            // Access the size argument directly
            Expr *SizeArg = Call->getArg(2)->IgnoreImplicit();
            // Get the source range of this argument
            SourceLocation StartLoc = SizeArg->getSourceRange().getBegin();
            SourceLocation EndLoc = SizeArg->getSourceRange().getEnd();

            // Create a hard-coded integer literal '10' as a string
            std::string NewSize = "10";

            // Replace the existing size expression with '10'
            getRewriter().ReplaceText(SourceRange(StartLoc, EndLoc), NewSize);
        }
        return true; // Continue visiting other nodes
    }
};

// Register the mutator
static RegisterMutator<ChangeMemsetSize> M(
    "ChangeMemsetSize",
    "Changes the size argument of the memset call from sizeof(array) to 10.");