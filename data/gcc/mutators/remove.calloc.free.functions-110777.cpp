#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveCallocFreeFunction : public MutatorUsingBash, public RecursiveASTVisitor<RemoveCallocFreeFunction> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/remove.calloc.free.functions-110777.sh");
    }

private:
};

static RegisterMutator<RemoveCallocFreeFunction> M(
    "remove.calloc.free.functions", 
    "Removes a calloc function, a free function, an initializer, and a return 0 statement.");