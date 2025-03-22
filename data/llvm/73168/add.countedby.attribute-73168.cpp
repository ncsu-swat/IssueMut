#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddCountedbyAttribute : public MutatorUsingBash, public RecursiveASTVisitor<AddCountedbyAttribute> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/add.countedby.attribute-73168.sh");
    }
    
private:
};

static RegisterMutator<AddCountedbyAttribute> M(
    "add.countedby.attribute",
    "Adds a __attribute__((__counted_by__(size))) to a array variable.");
