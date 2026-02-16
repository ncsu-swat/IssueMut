#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveInitializer108657 : public Mutator, public RecursiveASTVisitor<RemoveInitializer108657> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (InitDecls.empty()) return false;

        VarDecl *TargetDecl = randElement(InitDecls); //InitDecls[0];
        SourceRange InitRange = TargetDecl->getInit()->getSourceRange();
        
        // Get the location of = sign
        SourceLocation EqualLoc = Lexer::getLocForEndOfToken(
            TargetDecl->getLocation(), 0, 
            getRewriter().getSourceMgr(),
            getASTContext().getLangOpts());

        // Remove from = to ;
        getRewriter().RemoveText(
            SourceRange(EqualLoc, InitRange.getEnd()));

        return true;
    }

    bool VisitVarDecl(VarDecl *Decl) {
        if (Decl->hasInit() && !Decl->isImplicit() /*&& 
            Decl->getNameAsString() == "f"*/) {
            InitDecls.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<VarDecl*> InitDecls;
};

static RegisterMutator<RemoveInitializer108657> X(
    "remove.initializer.108657", 
    "Removes initializer from variable declaration.");
