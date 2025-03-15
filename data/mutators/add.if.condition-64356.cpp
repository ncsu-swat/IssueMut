#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddIfCondition : public MutatorUsingBash, public RecursiveASTVisitor<AddIfCondition> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("if \\(([a-zA-Z_][a-zA-Z0-9_]*) == ([0-9]+)\\)", "if \\(\\(\\2 == \\2\\) \\&\\& \\(\\1 == \\2\\)\\)");
    }
    
private:
};

static RegisterMutator<AddIfCondition> M(
    "add.if.condition",
    "Add extra identity comparison expression to if condition.");
