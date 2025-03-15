#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddAvxTargetClonesAttribute : public MutatorUsingBash, public RecursiveASTVisitor<AddAvxTargetClonesAttribute> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("int ([a-zA-Z_][a-zA-Z0-9_]*)\\((.*)\\)", "int __attribute__\\(\\(target_clones\\(\"default,avx\"\\)\\)\\) \\1\\(\\2\\)");
    }
    
private:
};

static RegisterMutator<AddAvxTargetClonesAttribute> M(
    "add.avx.target.clones.attribute",
    "Adds __attribute__((target_clones(\"default,avx\"))) target_clones attribute to function declarator.");
