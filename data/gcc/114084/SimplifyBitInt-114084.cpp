#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class SimplifyBitInt : public MutatorUsingBash, public RecursiveASTVisitor<SimplifyBitInt> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/SimplifyBitInt-114084.sh");
    }

private:
};

static RegisterMutator<SimplifyBitInt> M(
    "SimplifyBitInt",
    "Simplifies BitInt cast expressions to standard integer literals.");