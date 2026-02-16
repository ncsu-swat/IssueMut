#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class SimplifyControlFlow : public MutatorUsingBash,
                          public RecursiveASTVisitor<SimplifyControlFlow> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceOne("([a-zA-Z0-9_\\>]\\s+[a-zA-Z_][a-zA-Z0-9_]*)\\((.*)\\);", "\\1\\(\\2\\)__attribute__((returns_twice));");
    }

private:
};

static RegisterMutator<SimplifyControlFlow> M(
    "simplify.ControlFlow",
    "Simplifies control flow by removing volatile qualifier and unnecessary variables"
);