#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ReturnCastMutator : public MutatorUsingBash, public RecursiveASTVisitor<ReturnCastMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceAll("return\\s+\\(.*\\)(.*);", "return \\1;");
    }

private:
};

static RegisterMutator<ReturnCastMutator> X(
    "return.cast.mutation",
    "Moves type casts from variable declarations to return statements.");