#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveTempVariable : public Mutator, 
                          public RecursiveASTVisitor<RemoveTempVariable> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (!TargetDecl || !StoreStmt || !TempDeclStmt)
            return false;

        // Remove the declaration, including trailing newlines/spaces
        SourceLocation DeclEnd = Lexer::getLocForEndOfToken(
            TempDeclStmt->getEndLoc(), 0, getRewriter().getSourceMgr(),
            getASTContext().getLangOpts());
        SourceLocation NextToken = 
            Lexer::findNextToken(DeclEnd, getRewriter().getSourceMgr(),
                               getASTContext().getLangOpts())->getLocation();
        getRewriter().RemoveText(SourceRange(TempDeclStmt->getBeginLoc(), 
                                           NextToken.getLocWithOffset(-1)));
        
        // Replace all uses of temp variable with original variable
        for (DeclRefExpr *Ref : TempVarRefs) {
            getRewriter().ReplaceText(Ref->getSourceRange(), InitVarName);
        }
        
        // Remove the final assignment, including trailing newlines/spaces
        SourceLocation StmtEnd = Lexer::getLocForEndOfToken(
            StoreStmt->getEndLoc(), 0, getRewriter().getSourceMgr(),
            getASTContext().getLangOpts());
        NextToken = 
            Lexer::findNextToken(StmtEnd, getRewriter().getSourceMgr(),
                               getASTContext().getLangOpts())->getLocation();
        getRewriter().RemoveText(SourceRange(StoreStmt->getBeginLoc(),
                                           NextToken.getLocWithOffset(-1)));
        
        return true;
    }

    bool VisitDeclStmt(DeclStmt *DS) {
        if (!DS->isSingleDecl())
            return true;
            
        if (VarDecl *VD = dyn_cast<VarDecl>(DS->getSingleDecl())) {
            if (VD->hasInit()) {
                if (DeclRefExpr *DRE = 
                    dyn_cast<DeclRefExpr>(VD->getInit()->IgnoreImplicit())) {
                    InitVarName = DRE->getNameInfo().getAsString();
                    TargetDecl = VD;
                    Target_Orig_Decl = dyn_cast<VarDecl>(DRE->getDecl());
                    TempDeclStmt = DS;
                }
            }
        }
        return true;
    }

    bool VisitDeclRefExpr(DeclRefExpr *DRE) {
        if (TargetDecl && DRE->getDecl() == TargetDecl) {
            TempVarRefs.push_back(DRE);
        }
        return true;
    }

    bool VisitBinaryOperator(BinaryOperator *BO) {
        if (!TargetDecl || !Target_Orig_Decl)
            return true;
            
        if (BO->getOpcode() == BO_Assign) {
            if (DeclRefExpr *LHS = dyn_cast<DeclRefExpr>(BO->getLHS())) {
                if (LHS->getDecl() == Target_Orig_Decl) {
                    if (DeclRefExpr *RHS = 
                        dyn_cast<DeclRefExpr>(BO->getRHS()->IgnoreImplicit())) {
                        if (RHS->getDecl() == TargetDecl) {
                            StoreStmt = BO;
                        }
                    }
                }
            }
        }
        return true;
    }

private:
    VarDecl *TargetDecl = nullptr;
    VarDecl *Target_Orig_Decl = nullptr;
    BinaryOperator *StoreStmt = nullptr;
    DeclStmt *TempDeclStmt = nullptr;
    std::string InitVarName;
    std::vector<DeclRefExpr*> TempVarRefs;
};

static RegisterMutator<RemoveTempVariable> M(
    "remove.temp.variable.112359", 
    "Removes temporary variable and replaces its uses with the original variable");