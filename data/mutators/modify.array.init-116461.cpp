#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ModifyArrayInitMutator : public MutatorUsingBash, 
    public RecursiveASTVisitor<ModifyArrayInitMutator> {
public:
    using MutatorUsingBash::MutatorUsingBash;

    bool mutate() override {
        return replaceOne("([a-zA-Z0-9_][a-zA-Z0-9_]*\\[.*\\])(\\s*=\\s*.*;)", "\\1\\2\\n\\1 = \\1 ? \\1 : 1;");
    }

private:
};

static RegisterMutator<ModifyArrayInitMutator> M(
    "modify.array.init",
    "Modifies array initialization and adds zero check.");