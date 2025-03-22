#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class SimplifyVectorInit : public Mutator, 
    public RecursiveASTVisitor<SimplifyVectorInit> {

public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetInits.empty()) return false;

        InitListExpr* Target = randElement(TargetInits);
        
        SourceRange Range = Target->getSourceRange();
        SourceLocation Start = Range.getBegin();
        SourceLocation End = Range.getEnd();
        
        std::string NewInit = "{ 9 }";
        getRewriter().ReplaceText(
            SourceRange(Start, End),
            NewInit
        );
        
        return true;
    }

    bool VisitInitListExpr(InitListExpr *E) {
        if (E->getNumInits() > 1) {
            if (auto VT = E->getType()->getAs<VectorType>()) {
                TargetInits.push_back(E);
            }
        }
        return true;
    }

private:
    std::vector<InitListExpr*> TargetInits;
};

static RegisterMutator<SimplifyVectorInit> M(
    "vector.SimplifyInit", 
    "Simplifies vector initialization lists."
);