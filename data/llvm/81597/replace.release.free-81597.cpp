#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class ReplaceReleaseFree : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceReleaseFree> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/replace.release.free-81597.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<ReplaceReleaseFree> M(
    "replace.release.free",
    "Replace release function with free");