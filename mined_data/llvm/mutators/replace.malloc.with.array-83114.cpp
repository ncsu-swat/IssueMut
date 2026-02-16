#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class ReplaceMallocWithArray : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceMallocWithArray> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/replace.malloc.with.array-83114.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<ReplaceMallocWithArray> M(
    "replace.malloc.with.array",
    "Replace malloc with array declaration, delete the free statement, and add [0] when the variable is called");