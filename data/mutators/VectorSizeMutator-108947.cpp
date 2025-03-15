#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class VectorSizeMutator : public MutatorUsingBash, public RecursiveASTVisitor<VectorSizeMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("__vector_size__ +\\([0-9]+\\)", "__vector_size__\\(32\\)");
    }

private:
};

static RegisterMutator<VectorSizeMutator> M(
    "VectorSizeMutator",
    "Modifies the vector size attribute from 4 to 32.");