#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

class RemoveCStyleCast : public MutatorUsingBash, public clang::RecursiveASTVisitor<RemoveCStyleCast> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("(\\(.*)\\(.*\\)([0-9]+)\\s*\\)\\s*;", "\\1\\2\\);");
    }

private:
};

static RegisterMutator<RemoveCStyleCast> M(
    "remove.cstylecast", 
    "Removes C-style casts from function arguments.");