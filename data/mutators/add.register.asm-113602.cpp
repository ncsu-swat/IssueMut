#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class AddRegisterAsm : public MutatorUsingBash, public RecursiveASTVisitor<AddRegisterAsm> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceOne("_BitInt\\(([0-9]+)\\) ([a-zA-Z_][a-zA-Z0-9_]*);", "register _BitInt(\\1) \\2 asm(\"\");");
    }

private:
};

static RegisterMutator<AddRegisterAsm> X(
    "add.register.asm", 
    "Adds register and asm(\"\") to BitInt variable declarations"
);