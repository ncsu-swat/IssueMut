#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ReplaceVoidPointerWithOstream : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceVoidPointerWithOstream> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("void \\*([a-zA-Z_][a-zA-Z0-9_]*)", "std::ostream \\&\\1");
    }
    
private:
};

static RegisterMutator<ReplaceVoidPointerWithOstream> M(
    "replace.void.pointer.with.ostream",
    "Replaces void pointer type with std::ostream & type.");
