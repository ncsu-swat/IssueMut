#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class Mutator104391_2 : public MutatorUsingBash, public RecursiveASTVisitor<Mutator104391_2> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/104391-2.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<Mutator104391_2> M(
    "mutator-104391-2",
    "Mutator 104391-2");