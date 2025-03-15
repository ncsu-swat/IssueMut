#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ReplaceZeroToVariable : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceZeroToVariable> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("int ([a-zA-Z_][a-zA-Z0-9_]*) =([^;]*) 0 ([^;]*);", "int \\1 =\\2 \\1 \\3;");
    }
    
private:
};

static RegisterMutator<ReplaceZeroToVariable> M(
    "replace.zero.to.variable",
    "Replaces '0' literal with a variable reference.");
