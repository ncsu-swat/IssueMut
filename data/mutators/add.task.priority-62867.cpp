#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"
#include <iostream>

using namespace clang;

class AddTaskPriority : public MutatorUsingBash, public RecursiveASTVisitor<AddTaskPriority> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceOne("#pragma omp task", "#pragma omp task priority\\(42\\)");
    }
    
private:
};

static RegisterMutator<AddTaskPriority> M(
    "add.task.priority",
    "Adds a priority level 42 to an omp task pragma.");
