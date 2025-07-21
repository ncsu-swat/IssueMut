#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveVarInit : public MutatorUsingBash, public RecursiveASTVisitor<RemoveVarInit> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.var.init-113699.sh");
    }

private:
};

static RegisterMutator<RemoveVarInit> M(
    "remove.var.init.113699", 
    "Removes initialization from variable declaration");