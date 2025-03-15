#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveMacroDefinition : public Mutator, public RecursiveASTVisitor<RemoveMacroDefinition> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        SourceManager &SM = getRewriter().getSourceMgr();
        
        // Get source range for #define directive
        SourceLocation Start = SM.getLocForStartOfFile(SM.getMainFileID());
        SourceLocation Define = findNextToken(Start, tok::hash);
        if (Define.isInvalid()) return false;

        // Get the end location including newline
        SourceLocation End = findEndOfLine(Define);
        if (End.isInvalid()) return false;
        
        // Remove the #define directive
        getRewriter().RemoveText(SourceRange(Define, End));
        
        return true;
    }

private:
    SourceLocation findNextToken(SourceLocation Start, tok::TokenKind Kind) {
        SourceManager &SM = getRewriter().getSourceMgr();
        LangOptions LangOpts = getASTContext().getLangOpts();
        
        Token Tok;
        Lexer Lex(Start, LangOpts, SM.getBufferData(SM.getMainFileID()).data(),
                  SM.getCharacterData(Start),
                  SM.getBufferData(SM.getMainFileID()).data() + 
                  SM.getFileIDSize(SM.getMainFileID()));
                  
        Lex.LexFromRawLexer(Tok);
        if (Tok.is(Kind)) return Tok.getLocation();
        return SourceLocation();
    }

    SourceLocation findEndOfLine(SourceLocation Start) {
        SourceManager &SM = getRewriter().getSourceMgr();
        LangOptions LangOpts = getASTContext().getLangOpts();
        
        const char *Data = SM.getCharacterData(Start);
        unsigned Offset = 0;
        while (Data[Offset] != '\n' && Data[Offset] != '\0') {
            Offset++;
        }
        return Start.getLocWithOffset(Offset);
    }
};

static RegisterMutator<RemoveMacroDefinition> M(
    "remove.macro.definition.115988",
    "Removes a macro definition from the source code.");