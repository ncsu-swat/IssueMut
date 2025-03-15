#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RelationalMutator : public MutatorUsingBash, public RecursiveASTVisitor<RelationalMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("!=", "==");
    }

private:
    std::vector<BinaryOperator*> Conditions;
    FunctionDecl *CurrentFunction = nullptr;
};

static RegisterMutator<RelationalMutator> X(
    "relational.mutator", 
    "Changes != operator to == operator");