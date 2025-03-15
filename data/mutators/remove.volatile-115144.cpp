#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveVolatileQualifier : public Mutator,
    public clang::RecursiveASTVisitor<RemoveVolatileQualifier> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (VolatileVars.empty()) return false;

        VarDecl *Var = randElement(VolatileVars);
        
        // Get source range for entire declaration
        SourceRange DeclRange = Var->getSourceRange();
        
        // Get the source text
        SourceManager &SM = getRewriter().getSourceMgr();
        CharSourceRange CharRange = CharSourceRange::getTokenRange(DeclRange);
        StringRef DeclText = Lexer::getSourceText(CharRange, SM, getASTContext().getLangOpts());
        
        // Remove 'volatile' from the declaration text
        std::string NewText = DeclText.str();
        size_t pos = NewText.find("volatile");
        if (pos != std::string::npos) {
            NewText.erase(pos, 9); // Remove "volatile "
        }

        // Replace the entire declaration
        getRewriter().ReplaceText(DeclRange, NewText);
            
        return true;
    }

    bool VisitVarDecl(VarDecl *Decl) {
        if (Decl->getType().isVolatileQualified()) {
            VolatileVars.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<VarDecl *> VolatileVars;
};

static RegisterMutator<RemoveVolatileQualifier> M(
    "remove.volatile.115144",
    "Removes volatile qualifier from variable declarations.");
