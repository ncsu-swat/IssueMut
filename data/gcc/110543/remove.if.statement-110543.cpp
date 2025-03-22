#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveIfStatement : public Mutator, public RecursiveASTVisitor<RemoveIfStatement> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (IfStmts.empty()) return false;

        // Select a random if statement to modify
        IfStmt *Target = randElement(IfStmts);
        
        // Get the compound statement inside the if
        if (Stmt *ThenStmt = Target->getThen()) {
            // Get the source range for the entire if statement
            SourceRange IfRange = Target->getSourceRange();
            
            std::string ThenStr = Lexer::getSourceText(
                CharSourceRange::getCharRange(ThenStmt->getSourceRange()),
                getRewriter().getSourceMgr(),
                getASTContext().getLangOpts()).str();
                
            // Check if then-body is compound statement
            if (isa<CompoundStmt>(ThenStmt)) {
                // Remove braces from compound statement
                ThenStr = ThenStr.substr(1, ThenStr.length()-2);
            }
            
            // Preserve indent level
            std::string Indent = "  ";
            ThenStr = Indent + ThenStr;
            
            // Replace the entire if statement with its body
            getRewriter().ReplaceText(IfRange, ThenStr);
            return true;
        }
        
        return false;
    }

    bool VisitIfStmt(IfStmt *IS) {
        IfStmts.push_back(IS);
        return true;
    }

private:
    std::vector<IfStmt *> IfStmts;
};

static RegisterMutator<RemoveIfStatement> M(
    "remove.if.statement", 
    "Removes if statement and keeps its body.");