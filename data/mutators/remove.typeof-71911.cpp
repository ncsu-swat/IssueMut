#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemoveTypeof : public MutatorUsingBash, public RecursiveASTVisitor<RemoveTypeof> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("typeof\\(([^\\)]*)\\)", "\\1");
    }
    
private:
};

static RegisterMutator<RemoveTypeof> M(
    "remove.typeof",
    "Removes typeof() function call.");
