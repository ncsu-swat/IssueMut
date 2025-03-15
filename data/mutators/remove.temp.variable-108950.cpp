#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveTempVariable : public MutatorUsingBash, public RecursiveASTVisitor<RemoveTempVariable> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/remove.temp.variable-108950.sh");
    }

private:
};

static RegisterMutator<RemoveTempVariable> M(
    "remove.temp.variable.108950", 
    "Removes temporary variable and replaces its uses with direct cast expression.");