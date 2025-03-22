#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ModifyNoStackProtectorAttribute : public MutatorUsingBash, public RecursiveASTVisitor<ModifyNoStackProtectorAttribute> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/modity.no_stack_protector.attribute-75235.sh");
    }
    
private:
};

static RegisterMutator<ModifyNoStackProtectorAttribute> M(
    "modity.no_stack_protector.attribute",
    "Modifies attribute((no_stack_protector)) to [[gnu::no_stack_protector]] or [[clang::no_stack_protector]].");
