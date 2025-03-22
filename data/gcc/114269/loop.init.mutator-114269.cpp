#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ForLoopInitMutator : public Mutator, 
                          public RecursiveASTVisitor<ForLoopInitMutator> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (ForStmts.empty()) return false;

        ForStmt *Target = randElement(ForStmts);
        Stmt *InitStmt = Target->getInit();
        if (!InitStmt) return false;

        Expr *Init = cast<Expr>(InitStmt);
        SourceLocation InitStart = Init->getBeginLoc();
        SourceLocation InitEnd = Init->getEndLoc();
        
        if (InitStart.isInvalid() || InitEnd.isInvalid())
            return false;

        // Get the variable name from init statement
        if (auto *BO = dyn_cast<BinaryOperator>(Init)) {
            if (auto *DRE = dyn_cast<DeclRefExpr>(BO->getLHS())) {
                std::string VarName = DRE->getNameInfo().getAsString();
                
                // Remove the initialization part and just keep the variable name
                SourceLocation End = Lexer::getLocForEndOfToken(InitEnd, 0,
                    getRewriter().getSourceMgr(),
                    getASTContext().getLangOpts());
                    
                getRewriter().ReplaceText(
                    SourceRange(InitStart, End),
                    VarName + ";");
                    
                // Change >= to <= and 0 to 10 in condition
                if (auto *Cond = Target->getCond()) {
                    if (auto *BO = dyn_cast<BinaryOperator>(Cond)) {
                        if (BO->getOpcode() == BO_GE) {
                            // Replace operator
                            SourceLocation OpLoc = BO->getOperatorLoc();
                            getRewriter().ReplaceText(
                                SourceRange(OpLoc, OpLoc.getLocWithOffset(1)),
                                "<=");
                                
                            // Replace RHS value
                            Expr *RHS = BO->getRHS();
                            getRewriter().ReplaceText(
                                RHS->getSourceRange(),
                                "10");
                        }
                    }
                }
                return true;
            }
        }
        return false;
    }

    bool VisitForStmt(ForStmt *FS) {
        if (FS && FS->getInit()) {
            ForStmts.push_back(FS);
        }
        return true;
    }

private:
    std::vector<ForStmt *> ForStmts;
};

static RegisterMutator<ForLoopInitMutator> X(
    "loop.init.mutator",
    "Mutates for loop initialization and condition.");