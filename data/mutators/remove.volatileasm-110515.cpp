#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveVolatileAsm : public MutatorUsingBash, 
    public RecursiveASTVisitor<RemoveVolatileAsm> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceOne("__builtin_memcpy\\s*\\(([^,]+),([^,]+),\\s*sizeof.*\\);", "\\1 = \\2;");
    }

private:
};

static RegisterMutator<RemoveVolatileAsm> X(
    "remove.volatileasm", 
    "Removes volatile assembly memory barrier.");