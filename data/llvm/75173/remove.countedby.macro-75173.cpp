#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemoveCountedbyMacro : public MutatorUsingBash, public RecursiveASTVisitor<RemoveCountedbyMacro> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.countedby.macro-75173.sh");
    }
    
private:
};

static RegisterMutator<RemoveCountedbyMacro> M(
    "remove.countedby.macro",
    "Removes a countedby macro and adds countedby attribute to another macro.");
