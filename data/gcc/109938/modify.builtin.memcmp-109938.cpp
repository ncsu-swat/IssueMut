#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ModifyBuiltInMemcmp : public MutatorUsingBash, 
    public RecursiveASTVisitor<ModifyBuiltInMemcmp> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("\\(__builtin_memcmp\\((.*)\\) != ([0-9]+)\\)", "\\(__builtin_memcmp\\(\\1 != \\2\\)\\)");
    }

private:
};

static RegisterMutator<ModifyBuiltInMemcmp> M(
    "modify.builtin.memcmp", 
    "Modifies the parenthesis of builtin_memcmp() function call.");