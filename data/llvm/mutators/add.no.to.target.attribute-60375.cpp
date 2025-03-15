#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddNoToTargetAttribute : public MutatorUsingBash, public RecursiveASTVisitor<AddNoToTargetAttribute> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("__attribute__\\(\\(target\\(\"([^\"]*)\"\\)\\)\\)", "__attribute__\\(\\(target\\(\"no-\\1\"\\)\\)\\)");
    }

private:
};

static RegisterMutator<AddNoToTargetAttribute> M(
    "add.no.to.target.attribute",
    "Adds no- to target attribute");
