#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class ReplaceBoolWithBoolConst : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceBoolWithBoolConst> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/replace.bool.with.bool.const-84784.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<ReplaceBoolWithBoolConst> M(
    "replace.bool.with.bool.const",
    "Replace _Bool with _Bool const");