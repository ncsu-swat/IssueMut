#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class BitIntMutator : public MutatorUsingBash, public RecursiveASTVisitor<BitIntMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("volatile\\s+_BitInt\\s*\\(\\s*[0-9]+\\s*\\)", "volatile _BitInt(255)");
    }

private:
};

static RegisterMutator<BitIntMutator> M(
    "BitIntMutator.113092",
    "Replaces integer variables with _BitInt(255) variables with large values."
);