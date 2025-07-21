#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class ReplaceStructDefWithDeclaration : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceStructDefWithDeclaration> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/replace.struct.def.with.declaration-88008.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<ReplaceStructDefWithDeclaration> M(
    "replace.struct.def.with.declaration",
    "Replace a full struct definition with only the declaration");