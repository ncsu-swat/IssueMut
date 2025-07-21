#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class ReplaceBuiltinClzWithClzg : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceBuiltinClzWithClzg> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/replace.builtin_clz.with.clzg-83075.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<ReplaceBuiltinClzWithClzg> M(
    "replace.builtin_clz.with.clzg",
    "Replace builtin_clz, builtin_clzl, or builtin_clzll with builtin_clzg");