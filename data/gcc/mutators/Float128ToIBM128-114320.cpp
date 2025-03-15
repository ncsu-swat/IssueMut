#include "Mutator.h"
#include "MutatorManager.h"
#include "MutatorUsingBash.h"
#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

using namespace clang;

class Float128Mutator : public MutatorUsingBash,
                        public RecursiveASTVisitor<Float128Mutator> {
public:
  using MutatorUsingBash::MutatorUsingBash;

  bool mutate() override { return replaceOne("__float128", "__ibm128"); }

private:
};

static RegisterMutator<Float128Mutator>
    M("Float128ToIBM128", "Replaces __float128 with __ibm type.");
