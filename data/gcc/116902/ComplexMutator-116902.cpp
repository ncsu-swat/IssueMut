#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ComplexMutator : public MutatorUsingBash, public RecursiveASTVisitor<ComplexMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/ComplexMutator-116902.sh");
    }

private:
};

static RegisterMutator<ComplexMutator> M(
    "ComplexMutator",
    "Performs complex mutations for loop modifications.");