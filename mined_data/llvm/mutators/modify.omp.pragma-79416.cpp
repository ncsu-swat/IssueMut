#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ModifyOmpPragma : public MutatorUsingBash, public RecursiveASTVisitor<ModifyOmpPragma> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("^(\\s*)#pragma\\s+omp\\s+teams\\s+parallel\\s+num_teams\\(([^\\)]*)\\)\\s+num_threads\\(([^\\)]*)\\)", "\\1#pragma omp teams num_teams(\\2)\\n\\1#pragma omp parallel num_threads(\\3)");
    }

private:
};

static RegisterMutator<ModifyOmpPragma> M(
    "modify.omp.pragma",
    "Converts a single combined #pragma omp teams parallel num_teams(var1) num_threads(var2) directive into two separate directives.");
