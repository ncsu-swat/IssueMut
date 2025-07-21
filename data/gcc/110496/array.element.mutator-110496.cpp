#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ArrayElementMutator : public MutatorUsingBash, public RecursiveASTVisitor<ArrayElementMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/array.element.mutator-110496.sh");
    }
private:
};

static RegisterMutator<ArrayElementMutator> X(
    "array.element.mutator",
    "Mutates array element assignments and adds do-while wrapper");