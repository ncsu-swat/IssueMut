#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveVolatileMutator : public MutatorUsingBash, public RecursiveASTVisitor<RemoveVolatileMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/remove.volatile-113295.sh");
    }

private:
};

static RegisterMutator<RemoveVolatileMutator> M(
    "remove.volatile.113295",
    "Removes volatile qualifiers and DMB barrier calls");