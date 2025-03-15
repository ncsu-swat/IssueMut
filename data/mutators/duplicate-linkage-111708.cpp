#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class DuplicateLinkageSpecMutator : public MutatorUsingBash,
    public RecursiveASTVisitor<DuplicateLinkageSpecMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/duplicate-linkage-111708.sh");
    }

private:
};

static RegisterMutator<DuplicateLinkageSpecMutator> X(
    "duplicate-linkage", 
    "Duplicates function declarations with opposite linkage specification"
);