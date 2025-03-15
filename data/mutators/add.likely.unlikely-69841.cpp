#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddLikelyUnlikely : public MutatorUsingBash, public RecursiveASTVisitor<AddLikelyUnlikely> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/add.likely.unlikely-69841.sh");
    }
    
private:
};

static RegisterMutator<AddLikelyUnlikely> M(
    "add.likely.unlikely",
    "Adds likely and unlikely attributes to if conditions.");
