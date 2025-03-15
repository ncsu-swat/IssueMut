#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddLongToDoubleTypedef : public MutatorUsingBash, public RecursiveASTVisitor<AddLongToDoubleTypedef> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("typedef double ([a-zA-Z_][a-zA-Z0-9_]*);", "typedef long double \\1;");
    }
    
private:
};

static RegisterMutator<AddLongToDoubleTypedef> M(
    "add.long.to.double.typedef",
    "Adds long to a typedef of double type.");
