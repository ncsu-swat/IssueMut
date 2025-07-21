#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class MaskComparisonMutator : public MutatorUsingBash,
    public RecursiveASTVisitor<MaskComparisonMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/mask.comparison-113609.sh");
    }

private:
};

static RegisterMutator<MaskComparisonMutator> X(
    "mask.comparison",
    "Replaces mask comparison literals with cast -1 expressions");