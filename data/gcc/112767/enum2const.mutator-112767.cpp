#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class EnumToConstMutator : public MutatorUsingBash, public RecursiveASTVisitor<EnumToConstMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceAll("\\s*enum\\s*\\{\\s*([a-zA-Z0-9_][a-zA-Z0-9_]*\\s*=\\s*[0-9]+)\\s*\\};", "const int \\1;");
    }
private:
};

static RegisterMutator<EnumToConstMutator> X(
    "enum2const.mutator",
    "Converts enum to const int and updates related uses.");