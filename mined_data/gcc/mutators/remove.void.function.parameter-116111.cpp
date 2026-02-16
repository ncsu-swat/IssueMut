#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemoveVoidFunctionParameter : public MutatorUsingBash, public RecursiveASTVisitor<RemoveVoidFunctionParameter> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.void.function.parameter-116111.sh");
    }

private:
};

static RegisterMutator<RemoveVoidFunctionParameter> M(
    "remove.void.function.parameter",
    "Removes a void function parameter and return statement.");