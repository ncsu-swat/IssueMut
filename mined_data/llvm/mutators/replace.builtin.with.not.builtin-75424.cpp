#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ReplaceBuiltinWithNotBuiltin : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceBuiltinWithNotBuiltin> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("__builtin_arm", "__arm");
    }
    
private:
};

static RegisterMutator<ReplaceBuiltinWithNotBuiltin> M(
    "replace.builtin.with.not.builtin",
    "Replaces __builtin_arm related functions with __arm functions.");
