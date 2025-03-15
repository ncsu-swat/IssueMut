#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddAssumeAnnotation : public MutatorUsingBash, public RecursiveASTVisitor<AddAssumeAnnotation> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("(.*->)(.*)\\(.*\\)\\s*;", "[[assume (\\1\\2)]];\\n\\1\\2();");
    }

private:
};

static RegisterMutator<AddAssumeAnnotation> M(
    "add.assume.annotation",
    "Adds [[assume()]] annotation before a function call");