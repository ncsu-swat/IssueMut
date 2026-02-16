#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveVolatile87523 : public MutatorUsingBash, public RecursiveASTVisitor<RemoveVolatile87523> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.volatile-87523.sh");
    }
};

static RegisterMutator<RemoveVolatile87523> M(
    "remove.volatile",
    "Removes volatile keyword from variables.");