#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveOptimizeAttribute : public MutatorUsingBash, public RecursiveASTVisitor<RemoveOptimizeAttribute> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("__attribute__\\s*\\(\\s*\\(\\s*optimize\\s*\\(\\s*\"O2\"\\s*\\)\\s*\\)\\s*\\)", "");
    }

private:
};

static RegisterMutator<RemoveOptimizeAttribute> X(
    "remove.optimize.attribute", 
    "Removes __attribute__((optimize(\"O2\"))) from function declarations.");