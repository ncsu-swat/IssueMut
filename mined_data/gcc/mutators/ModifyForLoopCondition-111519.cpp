#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"
#include <vector>

using namespace clang;

class ModifyForLoopCondition111519 : public Mutator, public clang::RecursiveASTVisitor<ModifyForLoopCondition111519> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        return !TargetForLoopPairs.empty() && modifyForLoop();
    }

    bool VisitForStmt(ForStmt *Stmt) {
        // Check if the initialization is a single element binary expression
        if (auto *Init = Stmt->getInit()) {
            // Check if it is a compound statement (could be a list of initializers)
            if (auto *InitList = dyn_cast<Expr>(Init)) {
                if (auto *VarAssign = dyn_cast<BinaryOperator>(InitList)) {
                    if (auto *DRE = dyn_cast<DeclRefExpr>(VarAssign->getLHS())) {
                        // Check if the declaration reference matches "g"
                        if (auto *VD = dyn_cast<VarDecl>(DRE->getDecl())) {
                            // if (VD->getName() == "g") {
                                // TargetForLoops.push_back(Stmt);
                            TargetForLoopPairs.push_back({Stmt, VD->getNameAsString()});
                            // }
                        }
                    }
                }
            }
        }
        return true;
    }

private:
    // std::vector<ForStmt *> TargetForLoops;
    std::vector<std::pair<ForStmt *, std::string>> TargetForLoopPairs;

    bool modifyForLoop() {
        // Choose one of the target for loops to modify
        auto Target = randElement(TargetForLoopPairs);
        ForStmt *ForLoop = Target.first;
        std::string VarName = Target.second;
        // ForStmt *ForLoop = randElement(TargetForLoops);
        if (!ForLoop) return false;

        // Get the condition expression (g < 2)
        if (auto *Cond = ForLoop->getCond()) {
            SourceLocation CondLoc = Cond->getBeginLoc();
            
            // New condition string
            std::string NewCondition = VarName + " <= 1";

            // Calculate the length of the old condition for replacement
            std::string OldCondition = Lexer::getSourceText(
                CharSourceRange::getTokenRange(Cond->getSourceRange()),
                getRewriter().getSourceMgr(), getASTContext().getLangOpts()).str();
            
            unsigned OldLength = OldCondition.length();

            // Replace the old condition with the new one
            getRewriter().ReplaceText(CondLoc, OldLength, NewCondition);

            return true;
        }
        return false;
    }
};

// Register the mutator
static RegisterMutator<ModifyForLoopCondition111519> M(
    "ModifyForLoopCondition",
    "Modifies the condition in a for loop from 'g < 2' to 'g <= 1'.");