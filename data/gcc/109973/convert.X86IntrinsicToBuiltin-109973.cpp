#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorUsingBash.h"
#include "MutatorManager.h"

using namespace clang;

class X86IntrinsicToBuiltin : public MutatorUsingBash, public RecursiveASTVisitor<X86IntrinsicToBuiltin> {
public:
    using MutatorUsingBash::MutatorUsingBash;
    
    bool mutate() override {
        return replaceWithBashScript("../scripts/convert.X86IntrinsicToBuiltin-109973.sh");
    }

private:
};

static RegisterMutator<X86IntrinsicToBuiltin> M(
    "convert.X86IntrinsicToBuiltin",
    "Converts x86 intrinsics to builtin operations.");