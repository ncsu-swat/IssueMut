#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ModifyArrayAllocation : public Mutator, 
    public RecursiveASTVisitor<ModifyArrayAllocation> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetTriples.empty()) return false;

        Triple TargetTriple = randElement(TargetTriples);
        BinaryOperator* assignOp = TargetTriple.AssignOp;
        BinaryOperator* multiplyOp = TargetTriple.MultiplyOp;
        std::string typeText = TargetTriple.TypeText;
        
        SourceLocation BeginLoc = multiplyOp->getOperatorLoc();
        SourceLocation EndLoc = multiplyOp->getSourceRange().getEnd();

        getRewriter().RemoveText(SourceRange(BeginLoc, EndLoc));
        std::string text = "(" + typeText + "*)";
        getRewriter().InsertTextBefore(assignOp->getRHS()->getSourceRange().getBegin(), text);

        return true;
    }

    bool VisitBinaryOperator(BinaryOperator *BO) {
        if (BO->getOpcode() == BO_Assign) {
            CurrentAssignOp = BO;
        }
        if (BO->getOpcode() == BO_Mul) {
            if (!CurrentAssignOp) return true;
            const auto *SizeofExpr = dyn_cast<UnaryExprOrTypeTraitExpr>(BO->getRHS());
            if (!SizeofExpr || SizeofExpr->getKind() != UETT_SizeOf) return true;

            if (SizeofExpr->isArgumentType()) {

                QualType TypeInside = SizeofExpr->getArgumentType();
                // Get the textual representation of the type
                std::string TypeText = TypeInside.getAsString();

                TargetTriples.push_back({CurrentAssignOp, BO, TypeText});
            }
        }
        return true;
    }

    bool VisitStmt(Stmt *S) {
        std::string StmtStr = getText(S);
        if (StmtStr.find(";") != std::string::npos) {
            CurrentAssignOp = nullptr;
        }
        return true;
    }

private:
    struct Triple {
        BinaryOperator *AssignOp;
        BinaryOperator *MultiplyOp;
        std::string TypeText;
    };
    BinaryOperator *CurrentAssignOp = nullptr;
    std::vector<Triple> TargetTriples;

    std::string getText(Stmt* S) {
        SourceRange Range = S->getSourceRange();
        return std::string(Lexer::getSourceText(
            CharSourceRange::getTokenRange(Range),
            getRewriter().getSourceMgr(),
            getASTContext().getLangOpts()));
    }
};

static RegisterMutator<ModifyArrayAllocation> M(
    "modify.array.allocation", 
    "Modifies array allocation expression.");