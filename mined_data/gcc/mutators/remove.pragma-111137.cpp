#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemovePragmaMutator : public Mutator, 
    public clang::RecursiveASTVisitor<RemovePragmaMutator> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (PragmaLocs.empty()) return false;

        // for (const auto &loc : PragmaLocs) {
        const auto &loc = randElement(PragmaLocs);
            // Remove the entire pragma line including newline
            getRewriter().RemoveText(
                SourceRange(loc.first, loc.second));
        // }
        
        return true;
    }

    bool VisitStmt(Stmt *s) {
        if (!s) return true;
        
        SourceManager &SM = getASTContext().getSourceManager();
        const auto &langOpts = getASTContext().getLangOpts();

        // Get source text around the statement
        SourceLocation startLoc = s->getBeginLoc();
        if (startLoc.isInvalid()) return true;

        startLoc = SM.getSpellingLoc(startLoc);
        
        // Look for #pragma token
        unsigned offset = SM.getFileOffset(startLoc);
        StringRef text = SM.getBufferData(SM.getFileID(startLoc));
        
        size_t pragmaPos = text.substr(0, offset).rfind("#pragma");
        if (pragmaPos != StringRef::npos) {
            SourceLocation pragmaLoc = SM.getLocForStartOfFile(SM.getFileID(startLoc))
                                     .getLocWithOffset(pragmaPos);
                                     
            // Get end of pragma line
            SourceLocation pragmaEndLoc = pragmaLoc;
            unsigned len = 0;
            while (len < text.size() && text[pragmaPos + len] != '\n') {
                len++;
            }
            pragmaEndLoc = pragmaLoc.getLocWithOffset(len);
            
            PragmaLocs.push_back(std::make_pair(pragmaLoc, pragmaEndLoc));
        }
        
        return true;
    }

private:
    std::vector<std::pair<SourceLocation, SourceLocation>> PragmaLocs;
};

static RegisterMutator<RemovePragmaMutator> X(
    "remove.pragma.111137", 
    "Removes pragma directives from the code");
