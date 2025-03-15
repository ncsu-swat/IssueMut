#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class AdjustPointerDeclarator : public MutatorUsingBash,
    public RecursiveASTVisitor<AdjustPointerDeclarator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("\\*\\*volatile ([a-zA-Z_][a-zA-Z0-9_]*)", "\\*volatile \\*\\1");
    }

private:
};

static RegisterMutator<AdjustPointerDeclarator> M(
    "adjust.PointerDeclarator",
    "Adjusts volatile pointer declarator ordering.");