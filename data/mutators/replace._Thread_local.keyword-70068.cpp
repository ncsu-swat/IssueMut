#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class Replace_Thread_localKeyword : public MutatorUsingBash, public RecursiveASTVisitor<Replace_Thread_localKeyword> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("_Thread_local", "thread_local");
    }
    
private:
};

static RegisterMutator<Replace_Thread_localKeyword> M(
    "replace._Thread_local.keyword",
    "Replaces _Thread_local into thread_local.");
