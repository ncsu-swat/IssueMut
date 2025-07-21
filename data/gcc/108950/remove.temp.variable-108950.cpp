#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveTempVariable108950 : public MutatorUsingBash, public RecursiveASTVisitor<RemoveTempVariable108950> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.temp.variable-108950.sh");
    }

private:
};

static RegisterMutator<RemoveTempVariable108950> M(
    "remove.temp.variable.108950", 
    "Removes temporary variable and replaces its uses with direct cast expression.");