#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddMusttailAttribute : public MutatorUsingBash, public RecursiveASTVisitor<AddMusttailAttribute> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("return ([a-zA-Z_][a-zA-Z0-9_]*\\([a-zA-Z_][a-zA-Z0-9_]*\\));", "[[clang::musttail]] return \\1;");
    }
    
private:
};

static RegisterMutator<AddMusttailAttribute> M(
    "add.musttail.attribute",
    "Adds clang-specific tail call optimization (TCO) attribute to a return statement.");
