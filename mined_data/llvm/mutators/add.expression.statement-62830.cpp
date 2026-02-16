#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddExpressionStatement : public MutatorUsingBash, public RecursiveASTVisitor<AddExpressionStatement> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/add.expression.statement-62830.sh");
    }
    
private:
};

static RegisterMutator<AddExpressionStatement> M(
    "add.expression.statement",
    "Adds an expression statement of a randomly picked integer variable.");
