#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveGlobalInit : public Mutator, 
    public clang::RecursiveASTVisitor<RemoveGlobalInit> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetVarDecls.empty()) return false;

        bool Changed = false;
        for (VarDecl* VD : TargetVarDecls) {
            if (VD->hasInit()) {
                SourceLocation DeclLoc = VD->getLocation();
                SourceLocation InitStart = VD->getInit()->getBeginLoc();
                SourceLocation InitEnd = VD->getInit()->getEndLoc();
                
                if (InitStart.isValid() && InitEnd.isValid()) {
                    // Get the source text from declaration to initializer
                    const SourceManager &SM = getASTContext().getSourceManager();
                    const LangOptions &LangOpts = getASTContext().getLangOpts();
                    
                    CharSourceRange Range = CharSourceRange::getCharRange(DeclLoc, InitEnd);
                    StringRef Text = Lexer::getSourceText(Range, SM, LangOpts);
                    
                    // Find the equal sign
                    size_t EqualPos = Text.find('=');
                    if (EqualPos != StringRef::npos) {
                        SourceLocation EqualLoc = DeclLoc.getLocWithOffset(EqualPos);
                        
                        // Remove the initializer including the '='
                        CharSourceRange RemoveRange = CharSourceRange::getCharRange(
                            EqualLoc,
                            Lexer::getLocForEndOfToken(InitEnd, 0, SM, LangOpts)
                        );
                        
                        getRewriter().RemoveText(RemoveRange);
                        Changed = true;
                    }
                }
            }
        }
        
        return Changed;
    }

    bool VisitVarDecl(VarDecl* VD) {
        // Only target global variables with initialization
        if (VD->hasGlobalStorage() && !VD->isStaticLocal() && 
            !VD->isConstexpr() && VD->hasInit()) {
            SourceLocation Loc = VD->getLocation();
            const SourceManager &SM = getASTContext().getSourceManager();
            
            // Check if the location is in the main file
            if (SM.isInMainFile(Loc)) {
                TargetVarDecls.push_back(VD);
            }
        }
        return true;
    }

private:
    std::vector<VarDecl*> TargetVarDecls;
};

static RegisterMutator<RemoveGlobalInit> M(
    "remove.global.init",
    "Removes initialization values from global variable declarations."
);