#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class MultiplyToPowMutator : public Mutator, 
    public RecursiveASTVisitor<MultiplyToPowMutator> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetExprs.empty()) return false;

        // for (BinaryOperator* Target : TargetExprs) {
        BinaryOperator* Target = randElement(TargetExprs);
            // Get the operands 
            Expr* LHS = Target->getLHS();
            std::string LHSStr = getSourceText(LHS);
            
            // Create replacement text
            std::string Replacement = "(float)__builtin_pow(" + LHSStr + ", 2)";
            
            // Replace the whole multiplication expression
            getRewriter().ReplaceText(Target->getSourceRange(), Replacement);
        // }
        
        return true;
    }

    bool VisitBinaryOperator(BinaryOperator *E) {
        if (E->getOpcode() == BO_Mul) {
            // Check if it's a self multiplication (x * x)
            Expr* LHS = E->getLHS()->IgnoreImpCasts();
            Expr* RHS = E->getRHS()->IgnoreImpCasts();
            
            if (getSourceText(LHS) == getSourceText(RHS)) {
                TargetExprs.push_back(E);
            }
        }
        return true;
    }

private:
    std::vector<BinaryOperator*> TargetExprs;
    
    std::string getSourceText(Expr* E) {
        SourceLocation StartLoc = E->getBeginLoc();
        SourceLocation EndLoc = E->getEndLoc();
        
        SourceManager &SM = getASTContext().getSourceManager();
        return std::string(SM.getCharacterData(StartLoc),
                          SM.getCharacterData(Lexer::getLocForEndOfToken(EndLoc, 0, 
                              SM, getASTContext().getLangOpts())) - 
                          SM.getCharacterData(StartLoc));
    }
};

static RegisterMutator<MultiplyToPowMutator> M(
    "multiply.to.pow", 
    "Replaces multiplication of same values (x*x) with __builtin_pow(x,2)");