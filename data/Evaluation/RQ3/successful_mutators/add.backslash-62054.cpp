#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddBackslash : public MutatorUsingBash, public RecursiveASTVisitor<AddBackslash> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/add.backslash-62054.sh");
    }
    
private:
};

static RegisterMutator<AddBackslash> M(
    "add.backslash",
    "Adds bashslash after a forward slash.");
