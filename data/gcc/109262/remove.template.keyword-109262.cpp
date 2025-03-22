#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveTemplateKeyword : public MutatorUsingBash,
    public RecursiveASTVisitor<RemoveTemplateKeyword> {

public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("~/MetaMut/mutators/auto/remove.template.keyword-109262.sh");
    }

private:
};

static RegisterMutator<RemoveTemplateKeyword> X(
    "remove.template.keyword",
    "Removes template arguments from au<double> type");