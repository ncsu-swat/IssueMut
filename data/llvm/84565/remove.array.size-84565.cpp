#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

// Replace class name and description
class RemoveArraySize84565 : public MutatorUsingBash, public RecursiveASTVisitor<RemoveArraySize84565> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    // Replace script path with your actual bash script
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/scripts/remove.array.size-84565.sh");
    }
};

// Register with a unique name and clear description
static RegisterMutator<RemoveArraySize84565> M(
    "remove.array.size.84565",
    "Remove sizes from a fixed-size array declarations");