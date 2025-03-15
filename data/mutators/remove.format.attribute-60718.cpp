#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemoveFormatAttribute : public MutatorUsingBash, public RecursiveASTVisitor<RemoveFormatAttribute> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("__attribute__\\(\\(format\\(.*\\)\\)\\)", "");
    }
    
private:
};

static RegisterMutator<RemoveFormatAttribute> M(
    "remove.format.attribute",
    "Removes __attribute__((format(...))).");
