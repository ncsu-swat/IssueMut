#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class AddAvailabilityEnvironments : public MutatorUsingBash, public RecursiveASTVisitor<AddAvailabilityEnvironments> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/add.availability.environments-89802.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<AddAvailabilityEnvironments> M(
    "add.availability.environments",
    "Append four different environment tags to random _attribute_((availability(...))) entries");