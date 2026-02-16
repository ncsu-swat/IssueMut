#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class RemoveCasts : public MutatorUsingBash, public RecursiveASTVisitor<RemoveCasts> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.casts-84712.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<RemoveCasts> M(
    "remove.casts",
    "Remove casts from (type)var");