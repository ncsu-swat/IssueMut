#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class UnnecessaryCastRemover : public MutatorUsingBash, public RecursiveASTVisitor<UnnecessaryCastRemover> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/remove.unnecessary.cast-114975.sh");
    }

private:
};

static RegisterMutator<UnnecessaryCastRemover> X(
    "remove.unnecessary.cast", 
    "Removes unnecessary C-style casts from integer expressions.");