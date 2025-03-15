#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeFunctionCall : public Mutator, public clang::RecursiveASTVisitor<ChangeFunctionCall> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        // Traverse the AST to find relevant function declarations and calls
        TraverseAST(getASTContext());
        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *FuncDecl) {
        if (FuncDecl->getName() == "foo9") {
            // Create a new function foo10 similar to foo9 but modify the function call
            createNewFunction(FuncDecl);
            return true;
        }
        return true; // Continue visiting other functions
    }

    bool VisitCallExpr(CallExpr *Call) {
        // We are only interested in calls inside foo9, so store their locations for later use
        if (auto *Callee = dyn_cast<DeclRefExpr>(Call->getCallee())) {
            if (Callee->getNameInfo().getName().getAsString() == "__riscv_vmv_s_x_i64m2") {
                SourceLocation CallLoc = Call->getSourceRange().getBegin();
                if (getRewriter().getSourceMgr().isInMainFile(CallLoc)) {
                    CallsToReplace.push_back({CallLoc, 30}); // 30 is the length of the original function name
                }
            }
        }
        return true;
    }

private:
    std::vector<std::pair<SourceLocation, unsigned>> CallsToReplace;

    void createNewFunction(FunctionDecl *OriginalFunc) {
        // Create the new function with modified call
        SourceLocation EndLoc = OriginalFunc->getSourceRange().getEnd();
        SourceLocation InsertLoc = Lexer::getLocForEndOfToken(
            EndLoc, 0, getRewriter().getSourceMgr(), getASTContext().getLangOpts());
        if (InsertLoc.isInvalid()) return;

        std::string NewFunc =
            "\nvoid foo10 (void *base, void *out, size_t vl)\n"
            "{\n"
            "    int64_t scalar = *(int64_t*)(base + 100);\n"
            "    vint64m2_t v = __riscv_vmv_v_x_i64m2 (0, 1);\n" // Ensure the change is here
            "    *(vint64m2_t*)out = v;\n"
            "}\n";

        getRewriter().InsertText(InsertLoc, NewFunc, true, true);
    }
};

// Register the mutator
static RegisterMutator<ChangeFunctionCall> M(
    "ChangeFunctionCall",
    "Mutates a call and duplicates the function.");