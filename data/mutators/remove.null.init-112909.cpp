#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveNullInitializer : public MutatorUsingBash,
    public RecursiveASTVisitor<RemoveNullInitializer> {

public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("^(\\s*[a-zA-Z_].*\\s+\\**[a-zA-Z_][a-zA-Z_0-9]*)\\s*=\\s*NULL\\s*;", "\\1;");
    }

private:
};

static RegisterMutator<RemoveNullInitializer> X(
    "remove.null.init",
    "Removes NULL initializer from variable declarations.");