#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveCast : public MutatorUsingBash, public RecursiveASTVisitor<RemoveCast> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("\\(\\s*unsigned\\s*\\)", "");
    }

private:
};

static RegisterMutator<RemoveCast> X("remove.cast", 
    "Removes C-style cast expressions from unsigned to boolean comparisons.");