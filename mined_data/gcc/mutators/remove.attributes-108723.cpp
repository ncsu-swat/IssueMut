#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveAttributes108723 : public MutatorUsingBash, public RecursiveASTVisitor<RemoveAttributes108723> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("__attribute__\\(\\(.*\\)\\)", "");
    }

private:
};

static RegisterMutator<RemoveAttributes108723> M(
    "remove.attributes", 
    "Removes function attributes.");