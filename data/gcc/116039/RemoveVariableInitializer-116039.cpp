#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveVariableInitializer : public Mutator, public RecursiveASTVisitor<RemoveVariableInitializer> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetVarDecls.empty()) return false;

        // Select a variable declaration to mutate
        VarDecl *VD = randElement(TargetVarDecls);

        // Remove the initializer from the variable declaration
        if (!removeInitializer(VD)) {
            return false;
        }

        return true;
    }

    bool VisitVarDecl(VarDecl *VD) {
        if (VD->hasInit() && !VD->isImplicit() && VD->getLocation().isValid()) {
            // Exclude function parameters
            if (!isa<ParmVarDecl>(VD)) {
                TargetVarDecls.push_back(VD);
            }
        }
        return true;
    }

private:
    bool removeInitializer(VarDecl *VD) {
        SourceManager &SM = getSourceManager();
        LangOptions LangOpts = getASTContext().getLangOpts();

        // Get the end location of the variable's name
        SourceLocation VarNameEndLoc = Lexer::getLocForEndOfToken(VD->getLocation(), 0, SM, LangOpts);

        // Start looking for the '=' token from after the variable name
        SourceLocation TokLoc = VarNameEndLoc;

        Token Tok;
        while (true) {
            // Get the next token, skipping whitespace
            bool Invalid = Lexer::getRawToken(TokLoc, Tok, SM, LangOpts, true /*IgnoreWhiteSpace*/);
            if (Invalid) {
                // Could not get token
                return false;
            }

            if (Tok.is(tok::equal)) {
                // Found the '=' token
                SourceLocation EqualLoc = Tok.getLocation();

                // Get the end location of the initializer
                Expr *InitExpr = VD->getInit();
                SourceLocation InitEndLoc = InitExpr->getEndLoc();
                SourceLocation InitEndLocAdjusted = Lexer::getLocForEndOfToken(InitEndLoc, 1, SM, LangOpts);

                // Form the source range to remove (from '=' to the end of the initializer)
                SourceRange RemoveRange(EqualLoc, InitEndLocAdjusted);

                // Remove the text corresponding to the initializer
                getRewriter().RemoveText(RemoveRange);

                // Update the AST by removing the initializer
                VD->setInit(nullptr);
                VD->setInitStyle(VarDecl::CInit);

                return true;
            } else {
                // Move to the next token
                TokLoc = Tok.getEndLoc();

                if (TokLoc.isInvalid()) {
                    // Cannot proceed further
                    return false;
                }
            }
        }
    }

    std::vector<VarDecl *> TargetVarDecls;
};

// Register the mutator
static RegisterMutator<RemoveVariableInitializer> M(
    "RemoveVariableInitializer",
    "Removes the initializer from a variable declaration.");