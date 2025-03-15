#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveIntegerCasts : public Mutator, public RecursiveASTVisitor<RemoveIntegerCasts> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (CastExprs.empty()) return false;

        // for (auto *Cast : CastExprs) {
        auto *Cast = randElement(CastExprs);
            // Get the subexpression without any parentheses
            const Expr *SubExpr = Cast->getSubExpr()->IgnoreParenImpCasts();
            
            // Get the full text of the cast expression
            SourceRange CastRange = Cast->getSourceRange();
            CharSourceRange CharRange = CharSourceRange::getTokenRange(CastRange);
            
            // Get the text of just the subexpression
            std::string SubExprStr = getText(*SubExpr);
            
            // Replace the entire cast expression with the subexpression
            getRewriter().ReplaceText(CharRange, SubExprStr);
        // }
        
        return true;
    }

    bool VisitCStyleCastExpr(CStyleCastExpr *Cast) {
        if (Cast->getType()->isIntegerType() && 
            Cast->getSubExpr()->getType()->isIntegerType()) {
            CastExprs.push_back(Cast);
        }
        return true;
    }

private:
    std::vector<CStyleCastExpr*> CastExprs;

    std::string getText(const Expr &E) {
        SourceRange Range = E.getSourceRange();
        return std::string(Lexer::getSourceText(
            CharSourceRange::getTokenRange(Range),
            getASTContext().getSourceManager(), 
            getASTContext().getLangOpts()));
    }
};

static RegisterMutator<RemoveIntegerCasts> M(
    "remove.integer.casts",
    "Removes C-style integer casts.");