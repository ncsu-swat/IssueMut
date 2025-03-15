#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ReplaceZeroLiteral : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceZeroLiteral> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("([^a-zA-Z0-9_])0([^a-zA-Z0-9_])", "\\10b0\\2");
    }
    
private:
};

static RegisterMutator<ReplaceZeroLiteral> M(
    "replace.0.with.0b0",
    "Replaces '0' literal with '0b0'.");
