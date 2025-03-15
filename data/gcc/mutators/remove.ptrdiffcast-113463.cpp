#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemovePtrdiffCast : public MutatorUsingBash, 
    public clang::RecursiveASTVisitor<RemovePtrdiffCast> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceOne("\\(\\s*ptrdiff_t\\s*\\)", "");
    }

private:
};

// Register the mutator
static RegisterMutator<RemovePtrdiffCast> M(
    "remove.ptrdiffcast",
    "Removes ptrdiff_t cast from expressions.");