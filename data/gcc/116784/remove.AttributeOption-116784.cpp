#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveAttributeOption : public MutatorUsingBash,
    public RecursiveASTVisitor<RemoveAttributeOption> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.AttributeOption-116784.sh");
    }

private:
};

static RegisterMutator<RemoveAttributeOption> M(
    "remove.AttributeOption",
    "Removes optimization from function attributes.");