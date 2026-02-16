#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ConvertToZeroInitialization : public MutatorUsingBash, public RecursiveASTVisitor<ConvertToZeroInitialization> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("int ([a-zA-Z_][a-zA-Z0-9_]*) = [0-9]+;", "int \\1 = 0;");
    }
    
private:
};

static RegisterMutator<ConvertToZeroInitialization> M(
    "convert.to.zero.initialization",
    "Convert a integer initialization into zero initialization.");
