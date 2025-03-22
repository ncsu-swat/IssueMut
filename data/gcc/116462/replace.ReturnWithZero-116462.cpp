#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ReplaceReturnWithZero : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceReturnWithZero> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/replace.ReturnWithZero-116462.sh");
    }

private:
};

static RegisterMutator<ReplaceReturnWithZero> M(
    "replace.ReturnWithZero", 
    "Replaces a return statement expression with 0.");