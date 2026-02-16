#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddLoaderUninitializedAttribute : public MutatorUsingBash, public RecursiveASTVisitor<AddLoaderUninitializedAttribute> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("([a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*\\[.*\\]);", "\\1 __attribute__\\(\\(loader_uninitialized\\)\\);");
    }
    
private:
};

static RegisterMutator<AddLoaderUninitializedAttribute> M(
    "add.loader_uninitialized.attribute",
    "Adds attribute((loader_uninitialized)) to a array declaration.");
