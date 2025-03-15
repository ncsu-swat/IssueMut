#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveTypedef : public MutatorUsingBash, public RecursiveASTVisitor<RemoveTypedef> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("struct\\s+(.*)\\{", "struct \\{");
    }

private:
};

static RegisterMutator<RemoveTypedef> M(
    "removeTypedef", 
    "Removes typedef and replaces with inline struct definitions.");