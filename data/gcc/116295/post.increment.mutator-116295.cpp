#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class PostIncrementMutator : public MutatorUsingBash, 
                            public RecursiveASTVisitor<PostIncrementMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/post.increment.mutator-116295.sh");
    }

private:
};

static RegisterMutator<PostIncrementMutator> X(
    "post.increment.mutator", 
    "Converts pointer dereference and increment into post-increment form");