#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveAttribute : public MutatorUsingBash, public RecursiveASTVisitor<RemoveAttribute> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.attribute-89670.sh");
    }
};

static RegisterMutator<RemoveAttribute> M(
    "remove.attribute",
    "Removes attribute from functions.");