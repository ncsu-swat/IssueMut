#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class ReplaceVoidArrsizeWithVar : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceVoidArrsizeWithVar> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/replace.void.arrsize.with.var-89835.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<ReplaceVoidArrsizeWithVar> M(
    "replace.void.arrsize.with.var",
    "Replace size in a void casted array with a matching int variable");