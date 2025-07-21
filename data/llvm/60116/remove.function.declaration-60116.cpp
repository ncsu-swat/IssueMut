#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemoveFunctionDeclaration : public MutatorUsingBash, public RecursiveASTVisitor<RemoveFunctionDeclaration> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.function.declaration-60116.sh");
    }

private:
};

static RegisterMutator<RemoveFunctionDeclaration> M(
    "remove.function.declaration",
    "Removes function declaration that has an attribute.");
