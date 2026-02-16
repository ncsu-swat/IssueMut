#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class DoWhileToFor : public MutatorUsingBash, public RecursiveASTVisitor<DoWhileToFor> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/convert.DoWhileToFor-109743.sh");
    }
private:
};

static RegisterMutator<DoWhileToFor> X(
    "convert.DoWhileToFor", 
    "Converts do-while loop to for loop.");