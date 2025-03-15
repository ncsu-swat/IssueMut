#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveIfdefSolarisBlock : public Mutator,
    public RecursiveASTVisitor<RemoveIfdefSolarisBlock> {

public:
    using Mutator::Mutator;

    bool mutate() override {
        SourceManager &SM = getRewriter().getSourceMgr();
        
        // Find the start of the file
        SourceLocation Start = SM.getLocForStartOfFile(SM.getMainFileID());
        if (Start.isInvalid()) return false;

        // Get source text
        const char *Text = SM.getCharacterData(Start);
        if (!Text) return false;

        // Find the #ifdef __sun block
        // const char *IfdefPos = strstr(Text, "#ifdef __sun");
        const char *IfdefPos = strstr(Text, "#ifdef");
        if (!IfdefPos) return false;

        // Find corresponding #endif
        const char *EndifPos = strstr(IfdefPos, "#endif");
        if (!EndifPos) return false;

        // Get position after #endif including any following newlines
        const char *AfterEndif = EndifPos + strlen("#endif");
        while (*AfterEndif == '\n' || *AfterEndif == '\r')
            AfterEndif++;

        // Add one more newline to completely remove the endif
        AfterEndif++;

        // Calculate source ranges
        SourceLocation IfdefLoc = Start.getLocWithOffset(IfdefPos - Text);
        SourceLocation EndLoc = Start.getLocWithOffset(AfterEndif - Text);

        // Remove the entire block
        getRewriter().RemoveText(SourceRange(IfdefLoc, EndLoc));

        return true;
    }
};

static RegisterMutator<RemoveIfdefSolarisBlock> M(
    "remove.ifdefsolaris",
    "Removes the #ifdef __sun block from the beginning of the file.");