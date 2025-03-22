#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class AddParametersMutator : public MutatorUsingBash, public RecursiveASTVisitor<AddParametersMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/add.parameters-114132.sh");
    }

private:
};

static RegisterMutator<AddParametersMutator> M(
    "add.parameters",
    "Adds two parameters to function and handles __AVR_TINY__ conditional compilation.");