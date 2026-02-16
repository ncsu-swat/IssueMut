#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveTargetAttribute : public MutatorUsingBash, 
    public clang::RecursiveASTVisitor<RemoveTargetAttribute> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.target.attribute-110755.sh");
    }

private:
};

static RegisterMutator<RemoveTargetAttribute> M(
    "remove.target.attribute.110755", 
    "Removes target attribute from function declaration.");