#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ConvertExclamationBitTest : public MutatorUsingBash,
    public RecursiveASTVisitor<ConvertExclamationBitTest> {

public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/convert.exclamation.bit.test-109907.sh");
    }
private:
};

static RegisterMutator<ConvertExclamationBitTest> M(
    "convert.exclamation.bit.test",
    "Converts bit test expressions using !! to conditional operator form");