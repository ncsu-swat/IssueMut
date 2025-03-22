#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ModifyConditionMutator : public MutatorUsingBash, public RecursiveASTVisitor<ModifyConditionMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/modify.condition-115161.sh");
    }

private:
};

static RegisterMutator<ModifyConditionMutator> X("modify.condition", 
    "Modifies compound condition in if statement to simpler form.");