#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ArrayAndLoopMutator : public MutatorUsingBash, 
    public clang::RecursiveASTVisitor<ArrayAndLoopMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceOne("for *\\(\\s*[a-zA-Z_][a-zA-Z0-9_]*\\s*=[^;]*;\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\s*<[^;]*;", "for (; \\1;");
    }

private:
};

static RegisterMutator<ArrayAndLoopMutator> X(
    "array.loop.mutator",
    "Modifies array sizes from 3 to 2 and changes for loop initialization");