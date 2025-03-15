#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemoveInlineAttribute : public MutatorUsingBash, public RecursiveASTVisitor<RemoveInlineAttribute> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("inline ", "");
    }
    
private:
};

static RegisterMutator<RemoveInlineAttribute> M(
    "remove.inline.attribute",
    "Removes the inline attribute of a function declarator.");
