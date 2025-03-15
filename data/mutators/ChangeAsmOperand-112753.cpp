#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeAsmOperand : public Mutator, public clang::RecursiveASTVisitor<ChangeAsmOperand> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        return !TargetFunctions.empty(); // Return true if there are functions to mutate
    }

    bool VisitFunctionDecl(FunctionDecl *Decl) {
        if (Decl->hasBody()) {
            auto *Body = Decl->getBody();
            for (auto *Stmt : Body->children()) {
                if (auto *Asm = dyn_cast<AsmStmt>(Stmt)) {
                    SourceRange SR = Asm->getSourceRange();
                    std::string AsmText = Lexer::getSourceText(
                        CharSourceRange::getTokenRange(SR),
                        getRewriter().getSourceMgr(),
                        getASTContext().getLangOpts()
                    ).str();

                    // Check for the specific assembly operand to mutate
                    const std::string oldOperand = "\"f\"";
                    const std::string newOperand = "\"fm\"";

                    if (AsmText.find(oldOperand) != std::string::npos) {
                        std::string NewAsmText = AsmText;
                        // Correct replacement using std::string
                        size_t pos = 0;
                        while ((pos = NewAsmText.find(oldOperand, pos)) != std::string::npos) {
                             NewAsmText.replace(pos, oldOperand.length(), newOperand);
                             pos += newOperand.length(); // Move past the new string
                        }

                        // Replace the old asm statement with the new one
                        getRewriter().ReplaceText(SR, NewAsmText);
                        TargetFunctions.push_back(Decl);
                        break; // Found the assembly statement, no need to check more
                    }
                }
            }
        }
        return true;
    }

private:
    std::vector<FunctionDecl *> TargetFunctions;
};

// Register the mutator
static RegisterMutator<ChangeAsmOperand> M(
    "ChangeAsmOperand",
    "Modifies assembly operand in function definitions from 'f' to 'fm'.");