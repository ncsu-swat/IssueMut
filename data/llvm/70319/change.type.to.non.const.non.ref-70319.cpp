#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ChangeTypeToNonConstNonRef : public MutatorUsingBash, public RecursiveASTVisitor<ChangeTypeToNonConstNonRef> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("const ([a-zA-Z_][a-zA-Z0-9_]*) \\&", "\\1 ");
    }
    
private:
};

static RegisterMutator<ChangeTypeToNonConstNonRef> M(
    "change.type.to.non.const.non.ref",
    "Change a type into non-const and non-reference type.");
