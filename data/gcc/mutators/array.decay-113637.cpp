#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ArrayDecayMutator : public MutatorUsingBash, public RecursiveASTVisitor<ArrayDecayMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("(.*) \\(\\*\\)\\[\\(.*\\)(.*)\\]", "\\1[][\\2]");
    }
private:
};

static RegisterMutator<ArrayDecayMutator> M(
    "array.decay",
    "Converts array parameter declarations with explicit size to simpler form");