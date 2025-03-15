#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ModifyFunctionCall : public MutatorUsingBash, public RecursiveASTVisitor<ModifyFunctionCall> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceOne("if\\s*\\((.*\\(\\))\\s*==\\s*.*", "\\1;");
    }

private:
};

static RegisterMutator<ModifyFunctionCall> M(
    "modify.function.call",
    "Modifies the function call by removing the if condition.");