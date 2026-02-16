#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class Mutator92667 : public MutatorUsingBash, public RecursiveASTVisitor<Mutator92667> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/92667.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<Mutator92667> M(
    "mutator-92667",
    "Mutator 92667");