#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddDirective : public MutatorUsingBash, public RecursiveASTVisitor<AddDirective> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/add.directive-77871.sh");
    }
    
private:
};

static RegisterMutator<AddDirective> M(
    "add.directive",
    "Adds a directive to define an integer literal and replaces the references.");
