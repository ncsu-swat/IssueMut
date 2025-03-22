#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class SimplifyCode : public MutatorUsingBash, public RecursiveASTVisitor<SimplifyCode> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/SimplifyCode-113756.sh");
    }

private:
};

static RegisterMutator<SimplifyCode> X("SimplifyCode", "Simplifies code by removing casts and combining declarations");