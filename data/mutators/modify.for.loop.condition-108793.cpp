#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ModifyForLoopCondition : public MutatorUsingBash, public RecursiveASTVisitor<ModifyForLoopCondition> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("for \\((.*)\\!=(.*)\\)", "for (\\1>\\2)");
    }

private:
};

static RegisterMutator<ModifyForLoopCondition> X(
    "modify.for.loop.condition", 
    "Transforms a while loop to an equivalent for loop.");