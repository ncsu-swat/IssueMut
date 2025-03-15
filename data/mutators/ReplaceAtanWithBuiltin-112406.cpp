#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ReplaceAtanWithBuiltin : public Mutator, public clang::RecursiveASTVisitor<ReplaceAtanWithBuiltin> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        return mutated;
    }

    bool VisitCallExpr(CallExpr *callExpr) {
        // Check if the called function is "atan"
        if (FunctionDecl* funcDecl = dyn_cast<FunctionDecl>(callExpr->getDirectCallee())) {
            if (funcDecl->getName() == "atan") {
                // Get the source range of the call expression
                SourceRange range = callExpr->getSourceRange();

                // Create the replacement text
                std::string replacement = "__builtin_atan(";
                replacement += Lexer::getSourceText(CharSourceRange::getTokenRange(callExpr->getArg(0)->getSourceRange()), 
                                                      getRewriter().getSourceMgr(), 
                                                      getASTContext().getLangOpts());
                replacement += ")";

                // Replace the call to "atan" with "__builtin_atan"
                getRewriter().ReplaceText(range, replacement);
                
                mutated = true; // Indicate that a mutation occurred
            }
        }
        return true; // Continue traversing
    }

private:
    bool mutated = false; // Track whether a mutation has occurred
};

// Register the mutator
static RegisterMutator<ReplaceAtanWithBuiltin> M(
    "ReplaceAtanWithBuiltin",
    "Replaces calls to 'atan' with calls to '__builtin_atan'.");