#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemoveLengthOfArray : public MutatorUsingBash, public RecursiveASTVisitor<RemoveLengthOfArray> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("([a-zA-Z_][a-zA-Z0-9_]*) ([a-zA-Z_][a-zA-Z0-9_]*)\\[[0-9]+\\];", "\\1 \\2\\[\\];");
    }
    
private:
};

static RegisterMutator<RemoveLengthOfArray> M(
    "remove.length.of.array",
    "Removes the length of an array variable.");
