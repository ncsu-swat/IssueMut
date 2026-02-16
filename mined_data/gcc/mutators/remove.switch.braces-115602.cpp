#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveSwitchBraces : public Mutator, 
    public RecursiveASTVisitor<RemoveSwitchBraces> {

public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (SwitchStmts.empty()) return false;

        SwitchStmt *Target = randElement(SwitchStmts);
        if (!Target) return false;

        CompoundStmt *Body = dyn_cast<CompoundStmt>(Target->getBody());
        if (!Body || Body->body_empty()) return false;

        SourceLocation LBrace = Body->getLBracLoc();
        SourceLocation RBrace = Body->getRBracLoc();

        if (LBrace.isInvalid() || RBrace.isInvalid())
            return false;

        // Remove braces
        getRewriter().RemoveText(CharSourceRange::getCharRange(LBrace, 
            LBrace.getLocWithOffset(1)));
        getRewriter().RemoveText(CharSourceRange::getCharRange(RBrace, 
            RBrace.getLocWithOffset(1)));

        return true;
    }

    bool VisitSwitchStmt(SwitchStmt *S) {
        if (CompoundStmt *CS = dyn_cast<CompoundStmt>(S->getBody())) {
            SwitchStmts.push_back(S);
        }
        return true;
    }

private:
    std::vector<SwitchStmt*> SwitchStmts;
};

static RegisterMutator<RemoveSwitchBraces> M(
    "remove.switch.braces",
    "Removes braces around switch statement body.");