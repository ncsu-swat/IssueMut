#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ConvertStructToChar : public MutatorUsingBash, public RecursiveASTVisitor<ConvertStructToChar> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/convert.struct.to.char-62447.sh");
    }
    
private:
};

static RegisterMutator<ConvertStructToChar> M(
    "convert.struct.to.char",
    "Converts a struct having one char field into a char variable.");
