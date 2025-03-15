#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveBitIntCast : public MutatorUsingBash,
                        public RecursiveASTVisitor<RemoveBitIntCast> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceAll("\\(\\s*size_t\\s*\\)", "");
    }

private:
};

static RegisterMutator<RemoveBitIntCast> M(
    "remove.bitint.cast",
    "Removes C-style casts from _BitInt variables.");