#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddSmmintrinHeader : public MutatorUsingBash, public RecursiveASTVisitor<AddSmmintrinHeader> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/add.smmintrin.header-64664.sh");
    }
    
private:
};

static RegisterMutator<AddSmmintrinHeader> M(
    "add.smmintrin.header",
    "Adds #include <smmintrin.h> to the code.");
