#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ReplaceNullWithOne : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceNullWithOne> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("NULL", "1");
    }

private:
};

static RegisterMutator<ReplaceNullWithOne> M(
    "ReplaceNullWithOne",
    "Replaces NULL literals with 1 in conditional expressions."
);