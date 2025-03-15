#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class UnsignedToUint8Mutator : public MutatorUsingBash,
    public RecursiveASTVisitor<UnsignedToUint8Mutator> {

public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("unsigned", "uint8_t");
    }

private:
};

static RegisterMutator<UnsignedToUint8Mutator> M(
    "UnsignedToUint8Mutator", 
    "Converts unsigned to uint8.");