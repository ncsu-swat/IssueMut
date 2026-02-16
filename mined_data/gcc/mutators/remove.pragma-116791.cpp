#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemovePragma116791 : public Mutator, public RecursiveASTVisitor<RemovePragma116791> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        const SourceManager &SM = getASTContext().getSourceManager();
        const LangOptions &LangOpts = getASTContext().getLangOpts();
        
        // Get source file content
        FileID MainFileID = SM.getMainFileID();
        StringRef Buffer = SM.getBufferData(MainFileID);
        
        // Find pragma directives using raw source traversal
        size_t pos = 0;
        while ((pos = Buffer.find("#pragma", pos)) != StringRef::npos) {
            // Find start of line
            size_t lineStart = pos;
            while (lineStart > 0 && Buffer[lineStart-1] != '\n') {
                lineStart--;
            }
            
            // Find end of line
            size_t lineEnd = pos;
            while (lineEnd < Buffer.size() && Buffer[lineEnd] != '\n') {
                lineEnd++;
            }
            if (lineEnd < Buffer.size()) lineEnd++; // Include newline
            
            // Convert positions to SourceLocations
            SourceLocation StartLoc = SM.getLocForStartOfFile(MainFileID)
                                    .getLocWithOffset(lineStart);
            SourceLocation EndLoc = SM.getLocForStartOfFile(MainFileID)
                                  .getLocWithOffset(lineEnd);
            
            // Remove the pragma line
            getRewriter().RemoveText(SourceRange(StartLoc, EndLoc));
            
            pos = lineEnd;
        }
        
        return true;
    }

private:
    std::vector<CharSourceRange> PragmaLocations;
};

static RegisterMutator<RemovePragma116791> M(
    "remove.pragma.116791", 
    "Removes pragma directives from the source code");
