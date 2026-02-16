#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveAttributePrototype : public MutatorUsingBash, public RecursiveASTVisitor<RemoveAttributePrototype> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.attribute.prototype-85387.sh");
    }
};

static RegisterMutator<RemoveAttributePrototype> M(
    "remove.attribute.prototype",
    "Removes __attribute__ from function prototypes.");