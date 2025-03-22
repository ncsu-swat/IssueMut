#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ForLoopReverser : public MutatorUsingBash, public RecursiveASTVisitor<ForLoopReverser> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/ForLoopReverser-113114.sh");
    }

private:
};

static RegisterMutator<ForLoopReverser> X(
    "ForLoopReverser", 
    "Reverses a for loop by changing increment to decrement and adjusting conditions.");