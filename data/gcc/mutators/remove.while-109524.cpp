#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveWhileLoop : public MutatorUsingBash, public RecursiveASTVisitor<RemoveWhileLoop> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("while\\s*\\(\\s*1\\s*\\)\\s*\\{(.*)\\}", "\\1");
    }

private:
};

static RegisterMutator<RemoveWhileLoop> X(
    "remove.while",
    "Removes while(1) loops.");