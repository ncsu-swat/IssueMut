#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class MoveVariableToInnerScope : public MutatorUsingBash, 
    public RecursiveASTVisitor<MoveVariableToInnerScope> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/move.variable.to.inner.scope-108574.sh");
    }

private:
};

static RegisterMutator<MoveVariableToInnerScope> M(
    "move.variable.to.inner.scope",
    "Moves a variable declaration to an inner scope.");