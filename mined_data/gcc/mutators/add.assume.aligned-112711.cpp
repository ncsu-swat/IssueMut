#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class MemoryAssumeAligned : public Mutator, public RecursiveASTVisitor<MemoryAssumeAligned> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        // if (!MemcpyCall) return false;
        if (MemcpyCalls.empty()) return false;

        const CallExpr *MemcpyCall = randElement(MemcpyCalls);

        SourceLocation ArgLoc = MemcpyCall->getArg(0)->getBeginLoc();
        std::string NewArg = "__builtin_assume_aligned(";
        getRewriter().InsertTextBefore(ArgLoc, NewArg);
        
        // Add ", 1)" after the first argument
        SourceLocation ArgEndLoc = MemcpyCall->getArg(0)->getEndLoc();
        SourceLocation AfterArgLoc = Lexer::getLocForEndOfToken(
            ArgEndLoc, 0, getRewriter().getSourceMgr(), getASTContext().getLangOpts());
        getRewriter().InsertTextAfter(AfterArgLoc, ", 1)");

        return true;
    }

    bool VisitCallExpr(CallExpr *Call) {
        if (const FunctionDecl *Func = Call->getDirectCallee()) {
            if (Func->getBuiltinID() == Builtin::BI__builtin_memcpy) {
                // MemcpyCall = Call;
                MemcpyCalls.push_back(Call);
            }
        }
        return true;
    }

private:
    // const CallExpr *MemcpyCall = nullptr;
    std::vector<const CallExpr *> MemcpyCalls;
};

static RegisterMutator<MemoryAssumeAligned> M(
    "add.assume.aligned", 
    "Adds __builtin_assume_aligned to memory pointer in __builtin_memcpy call");