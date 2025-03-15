#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class OMPSingleToParallel : public MutatorUsingBash, public RecursiveASTVisitor<OMPSingleToParallel> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("#pragma omp single", "#pragma omp parallel num_threads(1)");
    }
    
private:
};

static RegisterMutator<OMPSingleToParallel> M(
    "omp.single.to.parallel",
    "Converts from single to parallel with one thread.");
