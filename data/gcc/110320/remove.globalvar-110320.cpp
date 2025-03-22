#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveGlobalUse : public Mutator, public RecursiveASTVisitor<RemoveGlobalUse> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (GlobalVarDeclNodes.empty() && GlobalVarStmts.empty()) 
            return false;
        
        for (auto *GlobalVarDeclNode : GlobalVarDeclNodes) {
            // Remove the global variable declaration with trailing whitespace
            SourceLocation DeclStart = GlobalVarDeclNode->getBeginLoc();
            SourceLocation DeclEnd = GlobalVarDeclNode->getEndLoc();
            SourceLocation AfterSemi = Lexer::findLocationAfterToken(DeclEnd, tok::semi, 
                getASTContext().getSourceManager(),
                getASTContext().getLangOpts(),
                /*SkipTrailingWhitespaceAndNewLine=*/true);
                
            getRewriter().RemoveText(SourceRange(DeclStart, AfterSemi));
        }

        for (auto *GlobalVarStmt : GlobalVarStmts) {
            // Remove the statement using the global variable with trailing newline
            SourceLocation StmtStart = GlobalVarStmt->getBeginLoc(); 
            SourceLocation StmtEnd = GlobalVarStmt->getEndLoc();
            SourceLocation AfterStmt = Lexer::findLocationAfterToken(StmtEnd, tok::semi,
                getASTContext().getSourceManager(),
                getASTContext().getLangOpts(),
                /*SkipTrailingWhitespaceAndNewLine=*/true);
                
            getRewriter().RemoveText(SourceRange(StmtStart, AfterStmt));
        }
        
        return true;
    }

    bool VisitVarDecl(VarDecl *VD) {
        if (VD->isExternallyVisible()/* && VD->getName() == "global_variable" */) {
            GlobalVarDeclNodes.push_back(VD);
        }
        return true;
    }

    bool VisitUnaryOperator(UnaryOperator *UO) {
        // if (UO->isIncrementOp()) {
            if (auto *DRE = dyn_cast<DeclRefExpr>(UO->getSubExpr())) {
                // if (DRE->getDecl()->getName() == "global_variable") {
                    bool found = false;
                    for (auto VarDeclNode : GlobalVarDeclNodes) {  // Range-based for loop
                        if (VarDeclNode == DRE->getDecl()) {
                            found = true;
                            break;
                        }
                    }
                    if (found) {
                        GlobalVarStmts.push_back(UO);
                    }
                // }
            }
        // }
        return true;
    }

private:
    std::vector<VarDecl *> GlobalVarDeclNodes;
    std::vector<UnaryOperator *> GlobalVarStmts;
};

static RegisterMutator<RemoveGlobalUse> M(
    "remove.globalvar", 
    "Removes global variable declaration and its usage.");