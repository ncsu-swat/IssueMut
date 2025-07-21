#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveInitializer115397 : public MutatorUsingBash, public RecursiveASTVisitor<RemoveInitializer115397> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("^(\\s*.*\\s+\\*\\s*[a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*0\\s*;", "\\1;");
    }

private:
};

static RegisterMutator<RemoveInitializer115397> M(
    "remove.initializer.115397", 
    "Removes initialization of pointer variables initialized to 0");