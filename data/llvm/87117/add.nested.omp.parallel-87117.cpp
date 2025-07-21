#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class AddNestedOmpParallel : public MutatorUsingBash, public RecursiveASTVisitor<AddNestedOmpParallel> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/add.nested.omp.parallel-87117.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<AddNestedOmpParallel> M(
    "add.nested.omp.parallel",
    "Set OpenMP active levels to 2 and inject a nested #pragma omp parallel num_threads around an existing one");