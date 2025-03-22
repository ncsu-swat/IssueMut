#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class VolatileRemover : public MutatorUsingBash, public RecursiveASTVisitor<VolatileRemover> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/remove.volatile-108540.sh");
    }

private:
};

static RegisterMutator<VolatileRemover> X(
    "remove.volatile.108540", 
    "Removes volatile qualifiers and replaces certain type names.");