#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddExternCharVariable : public MutatorUsingBash, public RecursiveASTVisitor<AddExternCharVariable> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/add.extern.char.variable-71645.sh");
    }
    
private:
};

static RegisterMutator<AddExternCharVariable> M(
    "add.extern.char.variable",
    "Adds an extern char variable to replace char** parameter of main function.");
