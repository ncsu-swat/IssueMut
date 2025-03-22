#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class SwitchLocUnusedAttribute : public MutatorUsingBash, 
    public RecursiveASTVisitor<SwitchLocUnusedAttribute> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/switch.loc.unused.attribute-59973.sh");
    }

private:
};

static RegisterMutator<SwitchLocUnusedAttribute> M(
    "switch.loc.unused.attribute",
    "Switch the location of unused attribute with type and identifier.");