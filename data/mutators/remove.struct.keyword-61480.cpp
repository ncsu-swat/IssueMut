#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemoveStructKeyword : public MutatorUsingBash, public RecursiveASTVisitor<RemoveStructKeyword> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("extern struct (.*);", "extern \\1;");
    }
    
private:
};

static RegisterMutator<RemoveStructKeyword> M(
    "remove.struct.keyword",
    "Removes struct keyword from an extern struct.");
