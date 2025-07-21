#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemovePragma80664 : public MutatorUsingBash, public RecursiveASTVisitor<RemovePragma80664> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.pragma-80664.sh");
    }
    
private:
};

static RegisterMutator<RemovePragma80664> M(
    "remove.pragma",
    "Removes a pragma.");
