#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveGnuAttribute : public MutatorUsingBash, public RecursiveASTVisitor<RemoveGnuAttribute> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("^\\s*static\\s+(.*)__attribute__\\s*\\(\\s*\\(.*aligned\\s*\\(.*;", "\\1;");
    }

private:
};

static RegisterMutator<RemoveGnuAttribute> X(
    "remove.gnuattribute", 
    "Removes GNU attributes and static storage class from variable declarations");