#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ModifyBitIntMutator : public MutatorUsingBash, public RecursiveASTVisitor<ModifyBitIntMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceAll("_BitInt\\s*\\([0-9]+\\)(\\s*\\**[A-Za-z]+)([0-9]+)", "_BitInt\\(\\2\\)\\1\\2");
    }

private:
};

static RegisterMutator<ModifyBitIntMutator> X(
    "modify.bitint",
    "Modifies _BitInt width based on variable name.");