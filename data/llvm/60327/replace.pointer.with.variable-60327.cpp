#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ReplacePointerWithVariable : public MutatorUsingBash, 
    public RecursiveASTVisitor<ReplacePointerWithVariable> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/replace.pointer.with.variable-60327.sh");
    }

private:
};

static RegisterMutator<ReplacePointerWithVariable> M(
    "replace.pointer.with.variable",
    "Replaces a pointer variable with the pointed variable and modifies the pointer variable references.");