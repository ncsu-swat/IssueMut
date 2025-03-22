#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemoveCaseStatement : public MutatorUsingBash, public RecursiveASTVisitor<RemoveCaseStatement> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("case [^:]*:", "");
    }
    
private:
};

static RegisterMutator<RemoveCaseStatement> M(
    "remove.case.statement",
    "Removes a random case statement.");
