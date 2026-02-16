#include "Mutator.h"
#include "MutatorManager.h"
#include "MutatorUsingBash.h"
#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

using namespace clang;

class CallExprToPointerMutator
    : public MutatorUsingBash,
      public RecursiveASTVisitor<CallExprToPointerMutator> {
public:
  using MutatorUsingBash::MutatorUsingBash;

  bool mutate() override {
    return replaceOne("= ([a-zA-Z_][a-zA-Z0-9_]*)\\(\\)", "= (int *)\\1");
  }

private:
};

static RegisterMutator<CallExprToPointerMutator>
    M("CallExprToPointer", "Replaces function call 'a()' with '(int *)a'");
