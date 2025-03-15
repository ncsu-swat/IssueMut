#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemoveStructInitializer : public MutatorUsingBash, public RecursiveASTVisitor<RemoveStructInitializer> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("struct ([a-zA-Z_][a-zA-Z0-9_]*) ([a-zA-Z_][a-zA-Z0-9_]*) = \\{.*\\};", "struct \\1 \\2 = \\{\\};");
    }
    
private:
};

static RegisterMutator<RemoveStructInitializer> M(
    "remove.struct.initializer",
    "Removes the initializer of a struct variable.");
