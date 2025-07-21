#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class BitIntMutator : public MutatorUsingBash, public RecursiveASTVisitor<BitIntMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/BitIntMutator-114762.sh");
    }
private:
};

static RegisterMutator<BitIntMutator> X(
    "BitIntMutator.114762", 
    "Mutates _BitInt(66) to _BitInt(65) and removes redundant cast.");