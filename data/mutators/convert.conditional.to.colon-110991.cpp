#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ConditionalExprToColonMutator : public Mutator, 
    public RecursiveASTVisitor<ConditionalExprToColonMutator> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetExprs.empty()) return false;

        ConditionalOperator *Target = randElement(TargetExprs);
        
        // Get text for the parts we need
        std::string condStr = getText(Target->getCond());
        std::string falseStr = getText(Target->getFalseExpr());
        
        // Remove parentheses from condition if present
        if (condStr[0] == '(' && condStr[condStr.length()-1] == ')') {
            condStr = condStr.substr(1, condStr.length()-2);
        }
        
        // Remove parentheses from false expr if present
        if (falseStr[0] == '(' && falseStr[falseStr.length()-1] == ')') {
            falseStr = falseStr.substr(1, falseStr.length()-2);
        }
        
        // Replace entire conditional with new format
        SourceRange Range(Target->getBeginLoc(), Target->getEndLoc());
        getRewriter().ReplaceText(Range, condStr + " ?: " + falseStr);
        
        return true;
    }

    bool VisitConditionalOperator(ConditionalOperator *CO) {
        Expr *TrueExpr = CO->getTrueExpr();
        if (IntegerLiteral *IL = dyn_cast<IntegerLiteral>(TrueExpr)) {
            if (IL->getValue() == 1) {
                TargetExprs.push_back(CO);
            }
        }
        return true;
    }

private:
    std::vector<ConditionalOperator*> TargetExprs;
    
    std::string getText(const Expr *E) {
        SourceRange Range(E->getBeginLoc(), E->getEndLoc());
        return std::string(Lexer::getSourceText(
            CharSourceRange::getTokenRange(Range),
            getRewriter().getSourceMgr(),
            getASTContext().getLangOpts()));
    }
};

static RegisterMutator<ConditionalExprToColonMutator> M(
    "convert.conditional.to.colon",
    "Converts ternary conditional expressions of the form (c ? 1 : x) to (c ?: x)");