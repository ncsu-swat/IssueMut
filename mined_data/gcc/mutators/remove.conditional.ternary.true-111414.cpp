#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveConditionalTernaryTrue : public MutatorUsingBash,
    public RecursiveASTVisitor<RemoveConditionalTernaryTrue> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("\\?\\s*1\\s*\\:", "\\?\\:");
    }

private:
};

static RegisterMutator<RemoveConditionalTernaryTrue> M(
    "remove.conditional.ternary.true",
    "Removes the true expression '1' from a ternary conditional operator.");