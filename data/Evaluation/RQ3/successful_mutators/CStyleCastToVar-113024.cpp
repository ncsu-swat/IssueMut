#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class CStyleCastToVar : public MutatorUsingBash, public RecursiveASTVisitor<CStyleCastToVar> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("return\\s*\\((.*)\\)\\s*(.*);", "\\1 y = \\2; return y;");
    }

private:
};

static RegisterMutator<CStyleCastToVar> M(
    "CStyleCastToVar", 
    "Replace C-style cast in return with variable declaration and return.");