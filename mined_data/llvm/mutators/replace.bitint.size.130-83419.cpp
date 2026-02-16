#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class ReplaceBitIntSize130 : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceBitIntSize130> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/replace.bitint.size.130-83419.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<ReplaceBitIntSize130> M(
    "replace.bitint.size.130",
    "Replace any number inside _BitInt() with 130");