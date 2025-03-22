#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class ReplaceInt8_tWithMacroParam : public MutatorUsingBash, public RecursiveASTVisitor<ReplaceInt8_tWithMacroParam> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/replace.int8_t.with.macro.param-111255.sh");
    }

private:
};

static RegisterMutator<ReplaceInt8_tWithMacroParam> M(
    "replace.int8_t.with.macro.param", 
    "Replaces a type int8_t with a parameter of macro-defined function.");