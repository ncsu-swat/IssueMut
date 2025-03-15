#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ConvertGotoToAsmGoto : public MutatorUsingBash,
    public RecursiveASTVisitor<ConvertGotoToAsmGoto> {

public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/convert.goto.asmgoto-110079.sh");
    }

private:
};

static RegisterMutator<ConvertGotoToAsmGoto> M(
    "convert.goto.asmgoto",
    "Converts goto statements to asm goto statements.");