#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ModifyArrayIndex : public Mutator, public RecursiveASTVisitor<ModifyArrayIndex> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (ArraySubscripts.empty()) return false;

        for (auto *Target : ArraySubscripts) {
            SourceLocation IndexLoc = Target->getIdx()->getSourceRange().getBegin();
            SourceLocation EndLoc = Target->getIdx()->getSourceRange().getEnd();
            
            if (IndexLoc.isInvalid() || EndLoc.isInvalid())
                continue;

            IntegerLiteral *IL = dyn_cast<IntegerLiteral>(Target->getIdx());
            if (IL && IL->getValue() == 0) {
                getRewriter().ReplaceText(SourceRange(IndexLoc, EndLoc), "1");
            }
        }
        
        return true;
    }

    bool VisitArraySubscriptExpr(ArraySubscriptExpr *E) {
        ArraySubscripts.push_back(E);
        return true;
    }

private:
    std::vector<ArraySubscriptExpr *> ArraySubscripts;
};

static RegisterMutator<ModifyArrayIndex> M(
    "array.ModifyIndex", 
    "Modifies array index from 0 to 1 in array subscript expressions.");