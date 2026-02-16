#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ModifyBuiltInRotateLeft : public MutatorUsingBash, public RecursiveASTVisitor<ModifyBuiltInRotateLeft> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("__builtin_rotateleft([0-9]+)\\((.*), (.*)\\) \\& (.*);", "__builtin_rotateleft\\1\\(\\(\\2 \\& \\4\\), \\3\\);");
    }
    
private:
};

static RegisterMutator<ModifyBuiltInRotateLeft> M(
    "modify.builtin.rotateleft",
    "Moves the bitwise & expression into __builtin_rotateleft().");
