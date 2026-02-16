#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class ReplaceBitIntSize257 : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceBitIntSize257> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/replace.bitint.size.257-85139.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<ReplaceBitIntSize257> M(
    "replace.bitint.size.257",
    "Replace _BitInt(256) with _BitInt(257)");