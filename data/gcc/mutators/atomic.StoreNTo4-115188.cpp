#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class AtomicStoreNTo4 : public MutatorUsingBash, public RecursiveASTVisitor<AtomicStoreNTo4> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("__atomic_store_n", "__atomic_store_4");
    }

private:
};

static RegisterMutator<AtomicStoreNTo4> M(
    "atomic.StoreNTo4", 
    "Replaces __atomic_store_n with __atomic_store_4");