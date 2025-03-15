#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ArrayToPointerMutator : public MutatorUsingBash,
    public clang::RecursiveASTVisitor<ArrayToPointerMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceAll("(_BitInt\\([0-9]+\\)) ([a-zA-Z_][a-zA-Z0-9_]*)\\[[0-9]+\\];", "\\1 *\\2;");
    }

private:
};

static RegisterMutator<ArrayToPointerMutator> M(
    "array.to.pointer",
    "Converts a BitInt array declaration to a pointer declaration.");