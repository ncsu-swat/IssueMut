#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveVolatileQualifier : public MutatorUsingBash,
    public RecursiveASTVisitor<RemoveVolatileQualifier> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceWithBashScript("../scripts/remove.volatile-111444.sh");
    }

private:
};

static RegisterMutator<RemoveVolatileQualifier> X(
    "remove.volatile.111444",
    "Removes volatile qualifier from variable declarations.");