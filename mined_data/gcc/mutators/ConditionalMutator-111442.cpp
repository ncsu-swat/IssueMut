#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ConditionalMutator : public MutatorUsingBash, public RecursiveASTVisitor<ConditionalMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("\\((.*)!=\\s*NULL\\s*\\)\\s*\\?", "\\1?");
    }

private:
};

static RegisterMutator<ConditionalMutator> M(
    "ConditionalMutator", 
    "Mutates conditional expressions by replacing != NULL with pointer check and adding modulo.");