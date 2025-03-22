#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ForToWhileMutator : public MutatorUsingBash, 
    public RecursiveASTVisitor<ForToWhileMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/transform.ForToWhile-113467.sh");
    }
    
private:
};

static RegisterMutator<ForToWhileMutator> X(
    "transform.ForToWhile",
    "Transforms a for loop into an equivalent while loop.");