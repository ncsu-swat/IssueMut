#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveAttributes : public MutatorUsingBash, public RecursiveASTVisitor<RemoveAttributes> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("__attribute__\\(\\(.*\\)\\)", "");
    }

private:
};

static RegisterMutator<RemoveAttributes> M(
    "remove.attributes", 
    "Removes function attributes.");