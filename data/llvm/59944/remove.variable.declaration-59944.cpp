#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemoveVariableDeclaration : public MutatorUsingBash, public RecursiveASTVisitor<RemoveVariableDeclaration> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/remove.variable.declaration-59944.sh");
    }

private:
};

static RegisterMutator<RemoveVariableDeclaration> M(
    "remove.variable.declaration",
    "Removes variable declaration that the variable was used for address of operator.");
