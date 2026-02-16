#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class BitmaskMutator : public MutatorUsingBash, public RecursiveASTVisitor<BitmaskMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/BitmaskMutator-111252.sh");
    }
};

static RegisterMutator<BitmaskMutator> X("BitmaskMutator", 
    "Converts bit manipulation code to template-based bitmask operations");