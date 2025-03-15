#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class BitIntWidthMutator : public MutatorUsingBash, public RecursiveASTVisitor<BitIntWidthMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/BitIntWidth-114696.sh");
    }

private:
};

static RegisterMutator<BitIntWidthMutator> M(
    "BitIntWidth", 
    "Increases the width of _BitInt type declarations.");