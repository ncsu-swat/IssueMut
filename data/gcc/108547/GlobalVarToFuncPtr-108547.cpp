#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class GlobalVarToFuncPtr : public MutatorUsingBash, public RecursiveASTVisitor<GlobalVarToFuncPtr> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/GlobalVarToFuncPtr-108547.sh");
    }

private:
};

static RegisterMutator<GlobalVarToFuncPtr> M(
    "GlobalVarToFuncPtr", 
    "Replaces global variable t with function pointer cast");