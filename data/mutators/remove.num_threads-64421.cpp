#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class RemoveNumThreads : public MutatorUsingBash, public RecursiveASTVisitor<RemoveNumThreads> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("([^a-zA-Z0-9_])num_threads\\([0-9]+\\)", "\\1");
    }
    
private:
};

static RegisterMutator<RemoveNumThreads> M(
    "remove.num_threads",
    "Removes num_threads() from omp pragma.");
