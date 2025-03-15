#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

class RemoveTypeCastsMutator : public MutatorUsingBash, 
                              public clang::RecursiveASTVisitor<RemoveTypeCastsMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/remove.typecasts-114028.sh");
    }

private:
};

static RegisterMutator<RemoveTypeCastsMutator> X(
    "remove.typecasts.114028", 
    "Removes C-style type casts.");