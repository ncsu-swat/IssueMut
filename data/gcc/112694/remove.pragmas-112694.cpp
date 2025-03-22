#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemovePragmas : public Mutator, public RecursiveASTVisitor<RemovePragmas> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        SourceManager &SM = getRewriter().getSourceMgr();
        FileID MainFileID = SM.getMainFileID();
        
        // Get full source text
        llvm::StringRef Text = SM.getBufferData(MainFileID);
        
        // Find and remove all pragma lines
        size_t Pos = 0;
        std::string NewText = Text.str();
        while ((Pos = NewText.find("#pragma", Pos)) != std::string::npos) {
            size_t EndLine = NewText.find('\n', Pos);
            if (EndLine == std::string::npos) break;
            
            NewText.erase(Pos, EndLine - Pos + 1);
        }
        
        // Remove extra newlines
        while (NewText.find("\n\n\n") != std::string::npos) {
            size_t pos = NewText.find("\n\n\n");
            NewText.replace(pos, 3, "\n\n");
        }
        
        // Replace entire file content
        SourceLocation Start = SM.getLocForStartOfFile(MainFileID);
        SourceLocation End = SM.getLocForEndOfFile(MainFileID);
        getRewriter().ReplaceText(SourceRange(Start, End), NewText);
        
        return true;
    }
};

static RegisterMutator<RemovePragmas> X("remove.pragmas", 
    "Removes all pragma directives from the source code.");