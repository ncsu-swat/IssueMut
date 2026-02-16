#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ReplacePointerBuiltinbitcast : public MutatorUsingBash, public RecursiveASTVisitor<ReplacePointerBuiltinbitcast> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/replace.pointer.builtinbitcast-94496.sh");
    }
};

static RegisterMutator<ReplacePointerBuiltinbitcast> M(
    "replace.pointer.builtinbitcast",
    "Replaces void pointer dereferences with __builtin_bit_cast.");