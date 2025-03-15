#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class LlbToLbMutator : public MutatorUsingBash, public RecursiveASTVisitor<LlbToLbMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("%llb", "%lb");
    }
    
private:
};

static RegisterMutator<LlbToLbMutator> M(
    "llb.to.lb.mutator",
    "Reduces print format long long to long type.");
