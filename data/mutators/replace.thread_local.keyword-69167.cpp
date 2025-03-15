#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ReplaceThread_localKeyword : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceThread_localKeyword> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("thread_local", "_Thread_local");
    }
    
private:
};

static RegisterMutator<ReplaceThread_localKeyword> M(
    "replace.thread_local.keyword",
    "Replaces thread_local into _Thread_local.");
