#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveArraySize87766 : public MutatorUsingBash, public RecursiveASTVisitor<RemoveArraySize87766> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.array.size-87766.sh");
    }
};

static RegisterMutator<RemoveArraySize87766> M(
    "remove.array.size.87766",
    "Removes the size of an array when declaring.");