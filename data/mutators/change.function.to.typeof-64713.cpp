#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ChangeFunctionToTypeof : public MutatorUsingBash, public RecursiveASTVisitor<ChangeFunctionToTypeof> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("([a-zA-Z_][a-zA-Z0-9_]*) ([a-zA-Z_][a-zA-Z0-9_]*)\\(([a-zA-Z_][a-zA-Z0-9_]*)\\);", "typeof\\(\\1\\(\\3\\)\\) \\2;");
    }
    
private:
};

static RegisterMutator<ChangeFunctionToTypeof> M(
    "change.function.to.typeof",
    "Change a function declaration into typeof() form.");
