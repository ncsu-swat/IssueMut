#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class MutateVoidFunctionDeclaration : public MutatorUsingBash, public RecursiveASTVisitor<MutateVoidFunctionDeclaration> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/mutate.void.function.declaration-109412.sh");
    }

private:
};

static RegisterMutator<MutateVoidFunctionDeclaration> M(
    "mutate.void.function.declaration",
    "Change a void function declaration into a function definition.");