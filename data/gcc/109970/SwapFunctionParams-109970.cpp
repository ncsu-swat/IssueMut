#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class SwapFunctionParams : public MutatorUsingBash, public RecursiveASTVisitor<SwapFunctionParams> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/SwapFunctionParams-109970.sh");
    }

private:
};

static RegisterMutator<SwapFunctionParams> M(
    "SwapFunctionParams", 
    "Swaps parameters in function foo's declaration and calls.");