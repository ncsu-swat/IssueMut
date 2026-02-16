#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class MergeHexadecimal : public MutatorUsingBash,
    public RecursiveASTVisitor<MergeHexadecimal> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/merge.hexadecimal-109566.sh");
    }

private:
};

static RegisterMutator<MergeHexadecimal> M(
    "merge.hexadecimal",
    "Merge two hexadecimals in OR operator into one hexadecimal.");