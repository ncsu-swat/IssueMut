#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ModifyAsmRegister : public MutatorUsingBash, public RecursiveASTVisitor<ModifyAsmRegister> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("asm\\(\"a[0-9]+\"\\)", "asm(\"sp\")");
    }
    
private:
};

static RegisterMutator<ModifyAsmRegister> M(
    "modify.asm.register",
    "Modifies an asm register to sp.");
