#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ReplaceVariableDeclWithTemporary : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceVariableDeclWithTemporary> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/replace.variable.decl.with.temp-110308.sh");
    }

private:
};

static RegisterMutator<ReplaceVariableDeclWithTemporary> M(
    "replace.variable.decl.with.temp", 
    "Replaces a variable declaration with a temporary object.");