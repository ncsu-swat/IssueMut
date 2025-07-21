#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class Mutator86969 : public MutatorUsingBash, public RecursiveASTVisitor<Mutator86969> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/86969.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<Mutator86969> M(
    "mutator-86969",
    "Mutator 86969");