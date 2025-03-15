#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemoveUint8Cast : public MutatorUsingBash, public RecursiveASTVisitor<RemoveUint8Cast> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("\\(uint8_t\\)", "");
    }
    
private:
};

static RegisterMutator<RemoveUint8Cast> M(
    "remove.uint8_t.cast",
    "Removes uint8_t casting.");
