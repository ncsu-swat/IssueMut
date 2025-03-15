#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveMacroDefinition : public MutatorUsingBash, public RecursiveASTVisitor<RemoveMacroDefinition> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceAll("asm\\s*\\(\\s*\"\"\\s*\\)\\s*;", "");
    }
};

static RegisterMutator<RemoveMacroDefinition> M(
    "remove.macro.definition.113921",
    "Removes the asm_goto macro definition and empty lines.");