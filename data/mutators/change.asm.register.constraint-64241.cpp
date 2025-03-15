#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ChangeAsmRegisterConstraint : public MutatorUsingBash, public RecursiveASTVisitor<ChangeAsmRegisterConstraint> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("asm(.*)\"f\"", "asm\\1\"r\"");
    }
    
private:
};

static RegisterMutator<ChangeAsmRegisterConstraint> M(
    "change.asm.register.constraint",
    "Change asm register from Floating-point register into General-purpose register.");
