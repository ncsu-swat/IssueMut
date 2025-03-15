#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class AddUnsignedCast : public Mutator, public RecursiveASTVisitor<AddUnsignedCast> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (ModuleStatements.empty()) return false;

        auto *stmt = randElement(ModuleStatements);
        BinaryOperator *binOp = dyn_cast<BinaryOperator>(stmt);
        if (!binOp || !binOp->getOperatorLoc().isValid()) return false;

        MemberExpr *LHS = dyn_cast<MemberExpr>(binOp->getLHS()->IgnoreParenImpCasts());
        MemberExpr *RHS = dyn_cast<MemberExpr>(binOp->getRHS()->IgnoreParenImpCasts());
        
        if (LHS) {
            SourceLocation start = LHS->getBeginLoc();
            getRewriter().InsertTextBefore(start, "(unsigned)");
        }
        if (RHS) {
            SourceLocation start = RHS->getBeginLoc();
            getRewriter().InsertTextBefore(start, "(unsigned)");
        }

        return true;
    }

    bool VisitBinaryOperator(BinaryOperator *E) {
        if (E->getOpcode() == BO_Rem || E->getOpcode() == BO_NE) {
            ModuleStatements.push_back(E);
        }
        return true;
    }

private:
    std::vector<Stmt*> ModuleStatements;
};

static RegisterMutator<AddUnsignedCast> X("add.unsigned.cast", 
    "Add unsigned cast to member expressions in modulo operations.");