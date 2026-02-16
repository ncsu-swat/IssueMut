#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveComplexNotZeroComparison : public MutatorUsingBash,
    public RecursiveASTVisitor<RemoveComplexNotZeroComparison> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("\\((.*)!=\\s*0\\)\\s*\\|\\|", "\\1 \\|\\|");
    }

private:
};

static RegisterMutator<RemoveComplexNotZeroComparison> M(
    "remove.complex.notzero",
    "Removes != 0 comparison from complex number in logical OR expression");