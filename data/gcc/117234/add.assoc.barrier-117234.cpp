#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class AddAssocBarrier : public MutatorUsingBash, public RecursiveASTVisitor<AddAssocBarrier> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/add.assoc.barrier-117234.sh");
    }

private:
};

static RegisterMutator<AddAssocBarrier> M(
    "add.assoc.barrier", 
    "Wraps return value with __builtin_assoc_barrier.");