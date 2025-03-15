#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveVariableInitialization : public Mutator, 
    public RecursiveASTVisitor<RemoveVariableInitialization> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (InitVarDecls.empty()) return false;

        VarDecl *Target = randElement(InitVarDecls);
        
        SourceRange InitRange = Target->getInit()->getSourceRange();
        
        // Get location after equals sign
        SourceLocation EqualLoc = Lexer::getLocForEndOfToken(
            Target->getLocation(), 0, 
            getRewriter().getSourceMgr(),
            getASTContext().getLangOpts());
            
        // Remove initialization
        getRewriter().RemoveText(
            SourceRange(EqualLoc, InitRange.getEnd()));
            
        return true;
    }

    bool VisitVarDecl(VarDecl *VD) {
        if (VD->hasInit() && !VD->isImplicit()) {
            InitVarDecls.push_back(VD);
        }
        return true;
    }

private:
    std::vector<VarDecl*> InitVarDecls;
};

static RegisterMutator<RemoveVariableInitialization> M(
    "remove.var.init.114264", 
    "Removes initialization from a variable declaration.");