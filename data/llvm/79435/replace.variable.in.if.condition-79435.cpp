#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ReplaceVariableInIfCondition : public MutatorUsingBash, 
    public RecursiveASTVisitor<ReplaceVariableInIfCondition> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/replace.variable.in.if.condition-79435.sh");
    }

private:
};

static RegisterMutator<ReplaceVariableInIfCondition> M(
    "replace.variable.in.if.condition",
    "Replace the variable in if condition with its initializer.");