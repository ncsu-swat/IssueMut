#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class SwapSudotOperands : public MutatorUsingBash, public RecursiveASTVisitor<SwapSudotOperands> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceOne("\\((.*),(.*),([^)]+)\\)", "\\(\\1,\\3,\\2)");
    }

private:
};

static RegisterMutator<SwapSudotOperands> X(
    "sve.SwapSudotOperands", 
    "Swaps the second and third operands of svsudot calls.");