#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ExternToStaticMutator : public MutatorUsingBash, 
                             public RecursiveASTVisitor<ExternToStaticMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("extern", "static");
    }

private:
};

static RegisterMutator<ExternToStaticMutator> M(
    "extern.to.static.sed",
    "Replaces 'extern' storage class specifier with 'static'.");