#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class IsDevicePtrToMap : public MutatorUsingBash, public RecursiveASTVisitor<IsDevicePtrToMap> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/omp.IsDevicePtrToMap-109837.sh");
    }

private:
};

static RegisterMutator<IsDevicePtrToMap> X(
    "omp.IsDevicePtrToMap",
    "Changes OpenMP is_device_ptr clauses to map(tofrom:) clauses"
);