#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class HhuToDMutator : public MutatorUsingBash, public RecursiveASTVisitor<HhuToDMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("%hhu", "%d");
    }
    
private:
};

static RegisterMutator<HhuToDMutator> M(
    "hhu.to.d.mutator",
    "Reduces print format unsigned to signed type.");
