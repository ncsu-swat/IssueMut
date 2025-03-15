#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class EmptyFunctionRemovalMutator : public MutatorUsingBash, public RecursiveASTVisitor<EmptyFunctionRemovalMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("(.*\\s*[a-zA-Z_][a-zA-Z0-9_]*\\s*\\(.*\\))\\s*\\{\\}", "\\1;");
    }

private:
};

static RegisterMutator<EmptyFunctionRemovalMutator> X("EmptyFunctionRemovalMutator", 
    "Converts empty function definitions to function declarations.");