#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemoveStructInitialization : public MutatorUsingBash, public RecursiveASTVisitor<RemoveStructInitialization> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("\\} ([a-zA-Z_][a-zA-Z0-9_]*) = \\{.*\\};", "\\} \\1 = \\{\\};");
    }
    
private:
};

static RegisterMutator<RemoveStructInitialization> M(
    "remove.struct.initialization",
    "Removes the initialization of a struct variable.");
