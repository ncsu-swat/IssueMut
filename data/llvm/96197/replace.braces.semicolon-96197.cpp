#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ReplaceBracesSemicolon : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceBracesSemicolon> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/replace.braces.semicolon-96197.sh");
    }
};

static RegisterMutator<ReplaceBracesSemicolon> M(
    "replace.braces.semicolon",
    "Replaces {} with ; when __attribute__ is present.");