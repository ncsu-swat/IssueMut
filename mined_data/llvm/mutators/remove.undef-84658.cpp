#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class RemoveUndef : public MutatorUsingBash, public RecursiveASTVisitor<RemoveUndef> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.undef-84658.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<RemoveUndef> M(
    "remove.undef",
    "Remove multiline #undef");