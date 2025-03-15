#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class MemcpyToMemmove : public MutatorUsingBash, public RecursiveASTVisitor<MemcpyToMemmove> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("__builtin_memcpy\\(&([^,]*), ([^,]*), sizeof\\((.*)\\)\\)", "\\1 = *(\\3 *)__builtin_memmove(\\&\\1, \\2, sizeof(\\3))");
    }

private:
};

static RegisterMutator<MemcpyToMemmove> M(
    "MemcpyToMemmove", 
    "Transforms __builtin_memcpy calls to __builtin_memmove with BitInt cast.");