#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ChangeSizetToLongLong : public MutatorUsingBash, public RecursiveASTVisitor<ChangeSizetToLongLong> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("([^a-zA-Z0-9_])size_t([^a-zA-Z0-9_])", "\\1long long\\2");
    }
    
private:
};

static RegisterMutator<ChangeSizetToLongLong> M(
    "change.sizet.to.longlong",
    "Change a type size_t into long long.");
