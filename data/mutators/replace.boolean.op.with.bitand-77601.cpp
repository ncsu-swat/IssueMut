#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ReplaceBooleanOpWithBitand : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceBooleanOpWithBitand> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne(" & ", " bitand ");
    }
    
private:
};

static RegisterMutator<ReplaceBooleanOpWithBitand> M(
    "replace.boolean.op.with.bitand",
    "Repalces a '&' operator with bitand.");
