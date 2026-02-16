#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class SwapAttributeOrder : public MutatorUsingBash, public RecursiveASTVisitor<SwapAttributeOrder> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/swap.attribute.order-87151.sh");
    }
};

static RegisterMutator<SwapAttributeOrder> M(
    "swap.attribute.order",
    "Swaps the order of attributes with the return type and name.");