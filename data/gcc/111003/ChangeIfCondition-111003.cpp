#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeIfCondition : public Mutator, public clang::RecursiveASTVisitor<ChangeIfCondition> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        return !TargetIfs.empty(); // Return true if mutations are found
    }

    bool VisitIfStmt(IfStmt *If) {
        // Check the condition of the if statement
        if (auto *UnaryOp = dyn_cast<UnaryOperator>(If->getCond())) {
            // Check if the condition is of the form `!m`
            if (UnaryOp->getOpcode() == UO_LNot) {
                // Get the inner expression (the variable) that the unary operator negates
                auto *VarDecl = dyn_cast<DeclRefExpr>(UnaryOp->getSubExpr()->IgnoreParenCasts());
                if (VarDecl/* && VarDecl->getNameInfo().getName().getAsString() == "m" */) {
                    // We found our target: if (!m)
                    
                    // Get the source range for the mutation
                    SourceLocation StartLoc = UnaryOp->getSourceRange().getBegin();
                    SourceLocation EndLoc = UnaryOp->getSourceRange().getEnd();
                    SourceLocation InsertLoc = Lexer::getLocForEndOfToken(
                        EndLoc, 1, getRewriter().getSourceMgr(), getASTContext().getLangOpts());
                    if (!InsertLoc.isInvalid()) {
                        // Replace `!m` with `m`
                        getRewriter().ReplaceText(StartLoc, 2, VarDecl->getNameInfo().getName().getAsString());
                        TargetIfs.push_back(If); // Record the modified if statement
                    }
                }
            }
        }
        return true; // Continue traversing
    }

private:
    std::vector<IfStmt *> TargetIfs; // Keep track of mutated if statements
};

// Register the mutator
static RegisterMutator<ChangeIfCondition> M(
    "ChangeIfCondition",
    "Changes the condition of if statements from 'if (!m)' to 'if (m)'.");