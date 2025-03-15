#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ReplaceIntegerLiteralWith6wb : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceIntegerLiteralWith6wb> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("([^a-zA-Z0-9_])[0-9][0-9][0-9]([^a-zA-Z0-9_])", "\\166666666666666666666wb\\2");
    }
    
private:
};

static RegisterMutator<ReplaceIntegerLiteralWith6wb> M(
    "replace.integer.literal.with.6wb",
    "Repalces a three-digit integer literal with 66666666666666666666wb.");
