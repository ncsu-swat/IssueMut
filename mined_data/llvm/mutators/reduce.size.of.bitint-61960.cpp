#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ReduceSizeOfBitInt : public MutatorUsingBash, 
    public RecursiveASTVisitor<ReduceSizeOfBitInt> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/reduce.size.of.bitint-61960.sh");
    }

private:
};

static RegisterMutator<ReduceSizeOfBitInt> M(
    "reduce.size.of.bitint",
    "Reduces the size of BitInt variable into a half and plus 1.");