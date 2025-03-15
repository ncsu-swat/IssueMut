#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveArrayAlignmentAttribute : public MutatorUsingBash,
    public RecursiveASTVisitor<RemoveArrayAlignmentAttribute> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("__attribute__\\s*\\(\\s*\\(\\s*aligned\\s*\\(.*\\)\\s*\\)\\s*\\)", "");
    }
    
private:
};

static RegisterMutator<RemoveArrayAlignmentAttribute> M(
    "remove.ArrayAlignment",
    "Removes alignment attributes from array declarations.");