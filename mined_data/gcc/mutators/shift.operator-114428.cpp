#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ShiftOperatorMutator : public MutatorUsingBash,
    public RecursiveASTVisitor<ShiftOperatorMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/shift.operator-114428.sh");
    }

private:
};

static RegisterMutator<ShiftOperatorMutator> X(
    "shift.operator",
    "Mutates shift operators by removing LHS cast and adding RHS cast");