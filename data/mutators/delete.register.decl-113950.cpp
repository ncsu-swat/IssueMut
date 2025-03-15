#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class DeleteRegisterDecl : public MutatorUsingBash, public RecursiveASTVisitor<DeleteRegisterDecl> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/delete.register.decl-113950.sh");
    }

private:
};

static RegisterMutator<DeleteRegisterDecl> X(
    "delete.register.decl", 
    "Deletes register variable declarations and their assignments.");