#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ConditionalToIfMutator : public MutatorUsingBash,
    public RecursiveASTVisitor<ConditionalToIfMutator> {
private:

public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("\\((.*)>>\\s*3\\s*\\)\\s*&\\s*1", "(\\1\\&0x8)!=0");
    }
};

static RegisterMutator<ConditionalToIfMutator> M(
    "transform.ConditionalToIf",
    "Transforms conditional operators to if statements.");