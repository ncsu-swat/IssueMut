#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddTargetClonesAttribute : public MutatorUsingBash, public RecursiveASTVisitor<AddTargetClonesAttribute> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("(target_clones\\([^)]*)\\)", "\\1, \"arch=x86-64-v2\", \"arch=x86-64-v3\", \"arch=x86-64-v4\"");
    }

private:
};

static RegisterMutator<AddTargetClonesAttribute> M(
    "add.target.clones.attribute",
    "Adds arch=x86-64-v2, arch=x86-64-v3, arch=x86-64-v4 to target_clones attribute");
