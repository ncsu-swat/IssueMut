#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class SimplifyEnumAndNullMutator : public MutatorUsingBash,
    public RecursiveASTVisitor<SimplifyEnumAndNullMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/SimplifyEnumAndNull-116179.sh");
    }
};

static RegisterMutator<SimplifyEnumAndNullMutator> X(
    "SimplifyEnumAndNull", 
    "Simplifies enum declarations and replaces nullptr/enum constants with numbers");