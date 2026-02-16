#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class BitfieldMutator : public MutatorUsingBash, public RecursiveASTVisitor<BitfieldMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne(":\\s*[0-9]+\\s*;", ":24;");
    }

private:
};

static RegisterMutator<BitfieldMutator> M(
    "transform.BitfieldMutator", 
    "Transforms regular int field to 24-bit bitfield and simplifies bitwise operations.");