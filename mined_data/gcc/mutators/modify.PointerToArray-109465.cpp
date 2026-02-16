#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class PointerToArrayMutator : public Mutator, public RecursiveASTVisitor<PointerToArrayMutator> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (PointerDecls.empty()) return false;

        auto *D = randElement(PointerDecls);
        SourceRange StarLoc = D->getSourceRange();
        
        // Remove the * from the pointer declaration
        getRewriter().RemoveText(
            CharSourceRange::getCharRange(
                D->getTypeSourceInfo()->getTypeLoc().getAs<PointerTypeLoc>().getStarLoc(), 
                D->getTypeSourceInfo()->getTypeLoc().getAs<PointerTypeLoc>().getStarLoc().getLocWithOffset(1)
            )
        );
        
        // Add [] after the identifier
        SourceLocation IdEnd = Lexer::getLocForEndOfToken(
            D->getLocation(), 0, getRewriter().getSourceMgr(), 
            getASTContext().getLangOpts());
        
        getRewriter().InsertText(IdEnd, "[]");
        
        return true;
    }

    bool VisitVarDecl(VarDecl *D) {
        if (D->hasExternalStorage() && D->getType()->isPointerType()) {
            QualType PT = D->getType();
            if (PT->getPointeeType()->isCharType()) {
                PointerDecls.push_back(D);
            }
        }
        return true;
    }

private:
    std::vector<VarDecl*> PointerDecls;
};

static RegisterMutator<PointerToArrayMutator> M(
    "modify.PointerToArray", 
    "Converts char pointer declarations to array declarations.");