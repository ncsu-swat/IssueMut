#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RegisterVarMutator : public MutatorUsingBash, 
    public clang::RecursiveASTVisitor<RegisterVarMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/register.mutator-112278.sh");
    }

private:
};

static RegisterMutator<RegisterVarMutator> X(
    "register.mutator",
    "Modifies register variable names and assembly constraints");