#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class UnionFieldMutator : public MutatorUsingBash, public RecursiveASTVisitor<UnionFieldMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/union.field.mutator-108959.sh");
    }
};

static RegisterMutator<UnionFieldMutator> X(
    "union.field.mutator",
    "Mutates union field access and removes return values");