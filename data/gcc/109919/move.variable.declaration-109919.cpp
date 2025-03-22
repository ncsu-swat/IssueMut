#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class MoveVariableDeclaration : public MutatorUsingBash,
    public RecursiveASTVisitor<MoveVariableDeclaration> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/move.variable.declaration-109919.sh");
    }

private:
};

static RegisterMutator<MoveVariableDeclaration> M(
    "move.variable.declaration",
    "Moves a variable declaration into a while loop body.");