#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class Mutator111147 : public MutatorUsingBash, public RecursiveASTVisitor<Mutator111147> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/111147.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<Mutator111147> M(
    "mutator-111147",
    "Mutator 111147");