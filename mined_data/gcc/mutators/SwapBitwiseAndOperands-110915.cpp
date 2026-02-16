#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class SwapBitwiseAndOperands : public Mutator, 
    public RecursiveASTVisitor<SwapBitwiseAndOperands> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetBinaryOperators.empty()) return false;

        BinaryOperator *BinOp = randElement(TargetBinaryOperators);
        Expr *LHS = BinOp->getLHS();
        Expr *RHS = BinOp->getRHS();
        
        SourceRange LHSRange = LHS->getSourceRange();
        SourceRange RHSRange = RHS->getSourceRange();

        std::string LHSStr = getText(LHSRange);
        std::string RHSStr = getText(RHSRange);

        getRewriter().ReplaceText(LHSRange, RHSStr);
        getRewriter().ReplaceText(RHSRange, LHSStr);

        return true;
        // return Modified;
    }

    bool VisitReturnStmt(ReturnStmt *Ret) {
        Expr *RetVal = Ret->getRetValue();
        if(!RetVal || !isa<BinaryOperator>(RetVal))
            return true;
            
        BinaryOperator *BinOp = cast<BinaryOperator>(RetVal);
        if(BinOp->getOpcode() != BO_And)
            return true;
        
        TargetBinaryOperators.push_back(BinOp);
        // Expr *LHS = BinOp->getLHS();
        // Expr *RHS = BinOp->getRHS();
        
        // if(!isa<ParenExpr>(LHS) || !isa<ParenExpr>(RHS))
        //     return true;
            
        // ParenExpr *LParen = cast<ParenExpr>(LHS);
        // ParenExpr *RParen = cast<ParenExpr>(RHS);
        
        // if(!isa<BinaryOperator>(LParen->getSubExpr()) || 
        //    !isa<BinaryOperator>(RParen->getSubExpr()))
        //     return true;

        // BinaryOperator *LHSBin = cast<BinaryOperator>(LParen->getSubExpr());
        // BinaryOperator *RHSBin = cast<BinaryOperator>(RParen->getSubExpr());

        // if(!isNeqCompare(LHSBin) || !isRelationalCompare(RHSBin))
        //     return true;

        // SourceRange LHSRange = LHS->getSourceRange();
        // SourceRange RHSRange = RHS->getSourceRange();

        // std::string LHSStr = getText(LHSRange);
        // std::string RHSStr = getText(RHSRange);

        // getRewriter().ReplaceText(LHSRange, RHSStr);
        // getRewriter().ReplaceText(RHSRange, LHSStr);
        // Modified = true;

        return true;
    }

private:
    // bool Modified = false;
    std::vector<BinaryOperator *> TargetBinaryOperators;

    bool isNeqCompare(BinaryOperator *BinOp) {
        return BinOp->getOpcode() == BO_NE;
    }

    bool isRelationalCompare(BinaryOperator *BinOp) {
        return BinOp->getOpcode() == BO_GT || BinOp->getOpcode() == BO_LT;
    }

    std::string getText(SourceRange Range) {
        return std::string(Lexer::getSourceText(
            CharSourceRange::getTokenRange(Range),
            getRewriter().getSourceMgr(),
            getASTContext().getLangOpts()));
    }
};

static RegisterMutator<SwapBitwiseAndOperands> M(
    "SwapBitwiseAndOperands",
    "Swaps the operands of bitwise AND when one is a != comparison and the other is a relational comparison.");