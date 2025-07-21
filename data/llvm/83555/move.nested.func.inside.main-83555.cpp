#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class MoveNestedFuncInsideMain : public MutatorUsingBash, public RecursiveASTVisitor<MoveNestedFuncInsideMain> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/move.nested.func.inside.main-83555.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<MoveNestedFuncInsideMain> M(
    "move.nested.func.inside.main",
    "Move a nested function to inside the main function");