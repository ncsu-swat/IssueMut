#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveAlignas : public MutatorUsingBash, public RecursiveASTVisitor<RemoveAlignas> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.alignas-109676.sh");
    }

private:
};

static RegisterMutator<RemoveAlignas> M(
    "remove.alignas", 
    "Removes alignas specifiers from declarations.");