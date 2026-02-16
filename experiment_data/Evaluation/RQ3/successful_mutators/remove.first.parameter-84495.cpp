#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class RemoveFirstParameter : public MutatorUsingBash, public RecursiveASTVisitor<RemoveFirstParameter> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.first.parameter-84495.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<RemoveFirstParameter> M(
    "remove.first.parameter",
    "Remove first parameter of a function and remove all parameter references");