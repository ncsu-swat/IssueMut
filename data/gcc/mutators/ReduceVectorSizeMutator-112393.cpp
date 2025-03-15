#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ReduceVectorSizeMutator : public MutatorUsingBash, 
    public RecursiveASTVisitor<ReduceVectorSizeMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/ReduceVectorSizeMutator-112393.sh");
    }

private:
};

static RegisterMutator<ReduceVectorSizeMutator> X(
    "ReduceVectorSizeMutator", 
    "Reduce vector size");