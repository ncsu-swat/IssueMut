#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveStaticDecls : public MutatorUsingBash, public RecursiveASTVisitor<RemoveStaticDecls> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("^\\s*static\\s+.*;", "");
    }

private:
};

static RegisterMutator<RemoveStaticDecls> M(
    "remove.static.decls",
    "Removes static array declarations and their initializations.");