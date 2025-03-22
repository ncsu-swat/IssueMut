#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddHeader : public MutatorUsingBash, public RecursiveASTVisitor<AddHeader> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/add.header-69889.sh");
    }
    
private:
};

static RegisterMutator<AddHeader> M(
    "add.header",
    "Adds a header 'x.inc' in the beginning of code.");
