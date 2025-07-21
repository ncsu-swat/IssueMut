#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveArraySizeRepeat : public MutatorUsingBash, public RecursiveASTVisitor<RemoveArraySizeRepeat> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.array.size.repeat-90330.sh");
    }
};

static RegisterMutator<RemoveArraySizeRepeat> M(
    "remove.array.size.repeat",
    "Removes the size of an array when declaring.");