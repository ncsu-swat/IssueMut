#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class ModifyReturnStatement : public MutatorUsingBash, public RecursiveASTVisitor<ModifyReturnStatement> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("return ([a-zA-Z_][a-zA-Z_0-9]*) == [0-9]+ \\? [0-9]+ : ([a-zA-Z_][a-zA-Z_0-9]*)\\(\\1\\);", "return \\2(\\1);");
    }
    
private:
};

static RegisterMutator<ModifyReturnStatement> M(
    "modify.return.statement",
    "Removes iterary expression from return statment.");
