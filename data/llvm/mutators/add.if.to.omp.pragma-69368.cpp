#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddIfToOmpPragma : public MutatorUsingBash, public RecursiveASTVisitor<AddIfToOmpPragma> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/add.if.to.omp.pragma-69368.sh");
    }
    
private:
};

static RegisterMutator<AddIfToOmpPragma> M(
    "add.if.to.omp.pragma",
    "Adds an if condition to omp directive.");
