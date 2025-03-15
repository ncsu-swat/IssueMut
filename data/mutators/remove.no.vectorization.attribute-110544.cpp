#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveNoVectorizationAttribute : public MutatorUsingBash, 
    public RecursiveASTVisitor<RemoveNoVectorizationAttribute> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("(, )*optimize\\(\"no\\-tree\\-vectorize\"\\)", "");
    }

private:
};

static RegisterMutator<RemoveNoVectorizationAttribute> M(
    "remove.no.vectorization.attribute",
    "Removes the optimize(\"no-tree-vectorize\") attribute from functions.");