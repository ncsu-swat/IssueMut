#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class SwapFunctionArgs : public Mutator, public RecursiveASTVisitor<SwapFunctionArgs> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetCalls.empty()) return false;
        
        // Select a random call to _mm512_fcmul_pch
        CallExpr *Call = randElement(TargetCalls);
        
        // Get the arguments
        Expr *Arg0 = Call->getArg(0);
        Expr *Arg1 = Call->getArg(1);
        
        // Get source ranges
        SourceRange Arg0Range = Arg0->getSourceRange();
        SourceRange Arg1Range = Arg1->getSourceRange();
        
        // Get the source text
        std::string Arg0Text = getText(Arg0Range);
        std::string Arg1Text = getText(Arg1Range);
        
        // Swap the arguments
        getRewriter().ReplaceText(Arg0Range, Arg1Text);
        getRewriter().ReplaceText(Arg1Range, Arg0Text);
        
        return true;
    }
    
    bool VisitCallExpr(CallExpr *Call) {
        if (FunctionDecl *Callee = Call->getDirectCallee()) {
            // if (Callee->getName() == "_mm512_fcmul_pch") {
            if (Callee->getNumParams() >= 2) {
                TargetCalls.push_back(Call);
            }
            // }
        }
        return true;
    }

private:
    std::vector<CallExpr *> TargetCalls;
    
    std::string getText(SourceRange Range) {
        return std::string(Lexer::getSourceText(
            CharSourceRange::getTokenRange(Range),
            getRewriter().getSourceMgr(),
            getASTContext().getLangOpts()));
    }
};

static RegisterMutator<SwapFunctionArgs> M(
    "SwapFunctionArgs", 
    "Swaps the arguments of _mm512_fcmul_pch function calls.");