#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class CStyleCastMutator : public MutatorUsingBash, public RecursiveASTVisitor<CStyleCastMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("size_t(\\s*[a-zA-Z0-9_]+[^)]*;)", "uint32_t\\1");
    }

private:
};

static RegisterMutator<CStyleCastMutator> X(
    "remove-cstyle-cast", 
    "Removes C-style cast expressions.");