#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class AtomicExchangeMutator : public Mutator, public clang::RecursiveASTVisitor<AtomicExchangeMutator> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());

        if (TargetFunctions.empty()) return false;
        auto *FuncDecl = randElement(TargetFunctions);

        SourceLocation StartLoc = FuncDecl->getSourceRange().getEnd();
        SourceLocation InsertLoc = Lexer::getLocForEndOfToken(
            StartLoc, 1, getRewriter().getSourceMgr(), getASTContext().getLangOpts());
        if (InsertLoc.isInvalid())
            return false;

        // Prepare the new lines to insert
        std::string NewCode = R"(
struct S init_x, init_s;
__atomic_load (&x, &init_x, __ATOMIC_RELAXED);
__atomic_load (&s, &init_s, __ATOMIC_RELAXED);

__analyzer_eval (s.a[0] == init_x.a[0]); 
__analyzer_eval (s.a[15] == init_x.a[15]); 
__analyzer_eval (r.a[0] == init_s.a[0]); 
__analyzer_eval (r.a[15] == init_s.a[15]); 
)";

        getRewriter().InsertText(InsertLoc, NewCode, true, true);

        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *FuncDecl) {
        // Check if the function is `test_atomic_exchange`
        if (FuncDecl->getNameAsString().find("atomic") != std::string::npos) {
            TargetFunctions.push_back(FuncDecl);
        }
        return true; // Continue visiting other function declarations
    }
private:
    std::vector<FunctionDecl *> TargetFunctions;
};

// Register the mutator
static RegisterMutator<AtomicExchangeMutator> M(
    "AtomicExchangeMutator",
    "Mutates the `test_atomic_exchange` function to add extra atomic loads and analyzer evaluations.");