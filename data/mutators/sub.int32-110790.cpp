#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class SubInt32Mutator : public MutatorUsingBash, public RecursiveASTVisitor<SubInt32Mutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("\\((.*)>>(.*)\\)\\s*&\\s*1", "\\(\\1\\& (((unsigned long int) 1L) << \\2\\) != 0");
    }

private:
};

static RegisterMutator<SubInt32Mutator> M(
    "sub.int32",
    "Subtracts 0 from integer literal 32 in division/modulo operations.");