#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class PointerDereference : public MutatorUsingBash, 
    public RecursiveASTVisitor<PointerDereference> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/pointer.dereference-112709.sh");
    }

private:
};

static RegisterMutator<PointerDereference> M(
    "pointer.dereference",
    "Converts a struct parameter to a pointer parameter.");