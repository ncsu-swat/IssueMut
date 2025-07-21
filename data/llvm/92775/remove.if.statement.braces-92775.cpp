#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class RemoveIfStatementBraces : public MutatorUsingBash, public RecursiveASTVisitor<RemoveIfStatementBraces> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.if.statement.braces-92775.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<RemoveIfStatementBraces> M(
    "remove.if.statement.braces",
    "Remove braces from if a statement block");