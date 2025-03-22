#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemovePragma : public MutatorUsingBash, public RecursiveASTVisitor<RemovePragma> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/remove.pragma-80664.sh");
    }
    
private:
};

static RegisterMutator<RemovePragma> M(
    "remove.pragma",
    "Removes a pragma.");
