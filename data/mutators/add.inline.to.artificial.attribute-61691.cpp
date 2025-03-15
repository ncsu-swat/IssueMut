#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddInlineToArtificialAttribute : public MutatorUsingBash, public RecursiveASTVisitor<AddInlineToArtificialAttribute> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("__attribute__\\(\\(__artificial__\\)\\)", "inline __attribute__\\(\\(__always_inline__\\)\\) __attribute__\\(\\(__artificial__\\)\\)");
    }
    
private:
};

static RegisterMutator<AddInlineToArtificialAttribute> M(
    "add.inline.to.artificial.attribute",
    "Adds inline keyword and always_inline attribute when there is an artificial attribute.");
