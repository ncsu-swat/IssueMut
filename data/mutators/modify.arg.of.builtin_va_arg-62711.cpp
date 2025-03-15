#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ModifyArgOfBuiltInVaArg : public MutatorUsingBash, public RecursiveASTVisitor<ModifyArgOfBuiltInVaArg> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("__builtin_va_arg\\(.*, (.*)\\)", "__builtin_va_arg\\(global, \\1\\)");
    }
    
private:
};

static RegisterMutator<ModifyArgOfBuiltInVaArg> M(
    "modify.arg.of.builtin_va_arg",
    "Modifies the first argument of __builtin_va_arg int a undefined variable called global.");
