#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class DuplicateFunctionCall : public MutatorUsingBash, public RecursiveASTVisitor<DuplicateFunctionCall> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("([_a-zA-Z][_a-zA-Z0-9]{0,30}\\([^;]*\\);)", "\\1\\1");
    }

private:
};

static RegisterMutator<DuplicateFunctionCall> M(
    "DuplicateFunctionCall",
    "Duplicates function calls in functions containing malloc.");