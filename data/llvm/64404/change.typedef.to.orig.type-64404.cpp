#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ChangeTypedefToOrigType : public MutatorUsingBash, public RecursiveASTVisitor<ChangeTypedefToOrigType> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/change.typedef.to.orig.type-64404.sh");
    }
    
private:
};

static RegisterMutator<ChangeTypedefToOrigType> M(
    "change.typedef.to.orig.type",
    "Change the type of variable (typedef) into its original type.");
