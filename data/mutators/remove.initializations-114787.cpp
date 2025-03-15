#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveInitializations : public MutatorUsingBash, public RecursiveASTVisitor<RemoveInitializations> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceAll("^\\s*[a-zA-Z_][a-zA-Z0-9_]*\\s*=\\s*0\\s*;", "");
    }

private:
};

static RegisterMutator<RemoveInitializations> M(
    "remove.initializations", 
    "Removes initialization statements at the beginning of functions.");