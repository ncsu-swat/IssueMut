#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class UnsignedToSignedChar : public MutatorUsingBash, public RecursiveASTVisitor<UnsignedToSignedChar> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("unsigned char", "signed char");
        
    }

private:
};

static RegisterMutator<UnsignedToSignedChar> M(
    "UnsignedToSignedChar.115152", 
    "Replaces 'unsigned char' with 'signed char' in global variable declarations.");