#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AssignVariableToRegister : public MutatorUsingBash, public RecursiveASTVisitor<AssignVariableToRegister> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("^([a-zA-Z_][a-zA-Z0-9_]*) ([a-zA-Z_][a-zA-Z0-9_]*);", "register \\1 \\2 __asm__\\(\"x15\"\\);");
    }
    
private:
};

static RegisterMutator<AssignVariableToRegister> M(
    "assign.variable.to.register",
    "Assigns a variable to x15 register.");
