#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddwbToLiteral : public MutatorUsingBash, public RecursiveASTVisitor<AddwbToLiteral> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("([0-9]+)u", "\\1uwb");
    }
    
private:
};

static RegisterMutator<AddwbToLiteral> M(
    "add.wb.to.literal",
    "Adds wb to [0-9]+u.");
