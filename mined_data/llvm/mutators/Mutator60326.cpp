#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class Mutator60326 : public MutatorUsingBash, public RecursiveASTVisitor<Mutator60326> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/60326.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<Mutator60326> M(
    "mutator-60326",
    "Mutator 60326");