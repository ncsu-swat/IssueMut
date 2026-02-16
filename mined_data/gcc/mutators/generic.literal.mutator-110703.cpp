#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class GenericLiteralMutator : public MutatorUsingBash,
    public RecursiveASTVisitor<GenericLiteralMutator> {

public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/generic.literal.mutator-110703.sh");
    }

private:
};

static RegisterMutator<GenericLiteralMutator> M(
    "generic.literal.mutator",
    "Mutates negative integer literals in _Generic expressions.");