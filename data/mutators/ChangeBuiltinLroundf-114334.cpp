#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeBuiltinLroundf : public Mutator, public clang::RecursiveASTVisitor<ChangeBuiltinLroundf> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        return true; // Indicate that mutations could happen
    }

    bool VisitCallExpr(CallExpr *callExpr) {
        // Ensure we are dealing with a valid callee
        if (auto *callee = dyn_cast<FunctionDecl>(callExpr->getCalleeDecl())) {
            if (callee->getName() == "__builtin_lroundf") {
                // Get the source location for the whole call expression
                SourceLocation startLoc = callExpr->getBeginLoc();
                SourceLocation endLoc = callExpr->getEndLoc();

                // Construct replacement text
                std::string replacementText = "__builtin_lroundf16";

                // Include the argument if it exists
                if (callExpr->getNumArgs() > 0) {
                    replacementText += '('; // Start of arguments
                    replacementText += Lexer::getSourceText(
                        CharSourceRange::getTokenRange(callExpr->getArg(0)->getSourceRange()),
                        getRewriter().getSourceMgr(),
                        getASTContext().getLangOpts());
                    replacementText += ')'; // End of arguments
                } else {
                    replacementText += "();"; // If no arguments, keep it valid
                }

                // Replace the entire call expression with the new text
                getRewriter().ReplaceText(SourceRange(startLoc, endLoc), replacementText);

                return true; // Indicate we made a mutation
            }
        }
        return true; // Continue visiting other nodes
    }
};

// Register the mutator
static RegisterMutator<ChangeBuiltinLroundf> M(
    "ChangeBuiltinLroundf",
    "Replaces calls to __builtin_lroundf with __builtin_lroundf16.");