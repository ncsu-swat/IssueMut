#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveRedundantCasts : public MutatorUsingBash, public RecursiveASTVisitor<RemoveRedundantCasts> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.redundant.casts-110142.sh");
    }

private:
};

static RegisterMutator<RemoveRedundantCasts> M(
    "remove.redundant.casts",
    "Removes redundant C-style casts in arithmetic expressions.");