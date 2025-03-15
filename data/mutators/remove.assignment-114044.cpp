#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveAssignmentStmt : public Mutator, 
    public RecursiveASTVisitor<RemoveAssignmentStmt> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (DeclStmts.empty()) return false;
        
        // for (auto *DS : DeclStmts) {
        auto *DS = randElement(DeclStmts);
            // Find the variable declaration
            VarDecl *VD = dyn_cast<VarDecl>(DS->getSingleDecl());
            // if (!VD) continue;

            // Get the initialization expression
            Expr* Init = VD->getInit();
            // if (!Init) continue;
            if (!Init) return false;

            // Get the source text for the init expression
            SourceRange InitRange = Init->getSourceRange();
            
            // Replace the entire declaration with just the init expression
            std::string InitText = getRewriter().getRewrittenText(InitRange);
            getRewriter().ReplaceText(DS->getSourceRange(), InitText + ";");
        // }
        
        return true;
    }

    bool VisitDeclStmt(DeclStmt *DS) {
        if (VarDecl *VD = dyn_cast<VarDecl>(DS->getSingleDecl())) {
            // if (VD->getName() == "result") {
                DeclStmts.push_back(DS);
            // }
        }
        return true;
    }

private:
    std::vector<DeclStmt*> DeclStmts;
};

static RegisterMutator<RemoveAssignmentStmt> M(
    "remove.assignment", 
    "Removes assignment of builtin function results.");