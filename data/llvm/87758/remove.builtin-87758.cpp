#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveBuiltin : public MutatorUsingBash, public RecursiveASTVisitor<RemoveBuiltin> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.builtin-87758.sh");
    }
};

static RegisterMutator<RemoveBuiltin> M(
    "remove.builtin",
    "Removes __builtin_.");