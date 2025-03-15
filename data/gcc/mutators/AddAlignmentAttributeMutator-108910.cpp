#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class AddAlignmentAttributeMutator : public MutatorUsingBash,
                                      public clang::RecursiveASTVisitor<AddAlignmentAttributeMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/AddAlignmentAttributeMutator-108910.sh");
    }

private:
};

// Register the mutator
static RegisterMutator<AddAlignmentAttributeMutator> M(
    "AddAlignmentAttributeMutator",
    "Adds an alignment attribute to a floating point local variable declaration.");