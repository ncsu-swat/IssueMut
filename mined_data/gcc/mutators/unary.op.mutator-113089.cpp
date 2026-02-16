#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class UnaryOpMutator : public Mutator, public RecursiveASTVisitor<UnaryOpMutator> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (Targets.empty()) return false;

        UnaryOperator* Target = randElement(Targets);
        
        std::string OpString = getText(*(Target->getSubExpr()));
        getRewriter().ReplaceText(Target->getSourceRange(), OpString+"--");

        return true;
    }

    bool VisitUnaryOperator(UnaryOperator *UO) {
        if (UO->getOpcode() == UO_PreDec) {
            Targets.push_back(UO);
        }
        return true;
    }

private:
    std::vector<UnaryOperator*> Targets;

    std::string getText(const Expr &E) {
        SourceRange Range = E.getSourceRange();
        return std::string(Lexer::getSourceText(
            CharSourceRange::getTokenRange(Range),
            getRewriter().getSourceMgr(),
            getASTContext().getLangOpts()));
    }
};

static RegisterMutator<UnaryOpMutator> X(
    "unary.op.mutator", 
    "Mutates unary operator (--) from prefix to post position");