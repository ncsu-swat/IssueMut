#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ArrayToScalarMutator : public MutatorUsingBash, public RecursiveASTVisitor<ArrayToScalarMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/array.to.scalar-110387.sh");
    }
    
private:
};

static RegisterMutator<ArrayToScalarMutator> M(
    "array.to.scalar",
    "Converts an array to individual scalar variables.");