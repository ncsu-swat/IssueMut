#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class TypeOfUnqual : public MutatorUsingBash, public RecursiveASTVisitor<TypeOfUnqual> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("typeof_unqual", "__typeof_unqual__");
    }
    
private:
};

static RegisterMutator<TypeOfUnqual> M(
    "typeof_unqual.to.__typeof_unqual__",
    "Repalces a typeof_unqual() with __typeof_unqual__().");
