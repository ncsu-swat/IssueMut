#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class AddTypedefOfStruct : public MutatorUsingBash, 
    public RecursiveASTVisitor<AddTypedefOfStruct> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/add.typedef.of.struct-114361.sh");
    }

private:
};

static RegisterMutator<AddTypedefOfStruct> M(
    "add.typedef.of.struct",
    "Adds typedef of struct");