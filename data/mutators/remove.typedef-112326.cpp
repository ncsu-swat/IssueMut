#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class TypedefRemover : public MutatorUsingBash, public RecursiveASTVisitor<TypedefRemover> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/remove.typedef-112326.sh");
    }

private:
};

static RegisterMutator<TypedefRemover> M(
    "remove.typedef",
    "Removes int32_t typedefs and replaces them with int.");