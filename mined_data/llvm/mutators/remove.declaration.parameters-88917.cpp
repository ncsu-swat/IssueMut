#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class RemoveDeclarationParameters : public MutatorUsingBash, public RecursiveASTVisitor<RemoveDeclarationParameters> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.declaration.parameters-88917.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<RemoveDeclarationParameters> M(
    "remove.declaration.parameters",
    "Empty a matching function declaration's parameter list");