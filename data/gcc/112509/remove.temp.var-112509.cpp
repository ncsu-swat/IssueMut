#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

class RemoveTempVar : public MutatorUsingBash, public clang::RecursiveASTVisitor<RemoveTempVar> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/remove.temp.var-112509.sh");
    }

private:
};

static RegisterMutator<RemoveTempVar> X(
    "remove.temp.var", 
    "Removes temporary variable and replaces its use with direct field access.");