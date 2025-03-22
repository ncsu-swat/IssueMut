#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveFunctionCall : public MutatorUsingBash, 
    public RecursiveASTVisitor<RemoveFunctionCall> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne(".*\\.[a-zA-Z0-9_][a-zA-Z0-9_]*\\(.*\\)\\s*;", "");
    }

private:
};

static RegisterMutator<RemoveFunctionCall> M(
    "RemoveFunctionCall",
    "Removes a call to m_fn1() function.");