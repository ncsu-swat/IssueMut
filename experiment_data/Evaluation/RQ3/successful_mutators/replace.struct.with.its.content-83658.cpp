#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class ReplaceStructWithItsContent : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceStructWithItsContent> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/replace.struct.with.its.content-83658.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<ReplaceStructWithItsContent> M(
    "replace.struct.with.its.content",
    "When struct structName is called, replace it with the content inside its declaration");