#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemoveVoidParameter : public MutatorUsingBash, public RecursiveASTVisitor<RemoveVoidParameter> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("\\(void\\)", "()");
    }
    
private:
};

static RegisterMutator<RemoveVoidParameter> M(
    "remove.void.parameter",
    "Removes a void parameter.");
