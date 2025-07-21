#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class VectorLongLongToInt128 : public MutatorUsingBash, 
    public RecursiveASTVisitor<VectorLongLongToInt128> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/vector.LongLongToInt128-110230.sh");
    }

private:
};

static RegisterMutator<VectorLongLongToInt128> M(
    "vector.LongLongToInt128",
    "Converts vector signed long long to vector signed __int128");