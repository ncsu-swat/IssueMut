#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemoveDevice : public MutatorUsingBash, public RecursiveASTVisitor<RemoveDevice> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("device\\(0\\)", "");
    }
    
private:
};

static RegisterMutator<RemoveDevice> M(
    "remove.device",
    "Removes device(0) from omp pragma.");
