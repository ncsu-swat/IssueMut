#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class AddPopcountgParameters : public MutatorUsingBash, public RecursiveASTVisitor<AddPopcountgParameters> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/add.popcountg.parameters-82058.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<AddPopcountgParameters> M(
    "add.popcountg.parameters",
    "Add new 4 variants of popcountg containing 4 random parameters");