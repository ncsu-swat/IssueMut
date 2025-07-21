#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class ReorderAlignasDeclaration : public MutatorUsingBash, public RecursiveASTVisitor<ReorderAlignasDeclaration> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/reorder.alignas.declaration-81472.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<ReorderAlignasDeclaration> M(
    "reorder.alignas.declaration",
    "Moves the alignas(N) specifier before the variable name where it originally appears after");