#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class AddLabeledBreakContinue : public Mutator, public RecursiveASTVisitor<AddLabeledBreakContinue> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (Statements.empty()) return false;

        auto *S = randElement(Statements);

        char label = 'a';
    // for (auto *S : Statements) {
        // Get location
        SourceLocation loc = S->getBeginLoc();
        
        // Add labels
        std::string labels = "";
        for (int i = 0; i < 3; i++) {
            labels += std::string(1, label++) + ": ";
        }
        labels += "\n";
        
        getRewriter().InsertTextBefore(loc, labels);

        // Process break/continue
        std::function<void(Stmt*)> processStmt = [&](Stmt *stmt) {
            if (!stmt) return;

            if (auto *breakS = dyn_cast<BreakStmt>(stmt)) {
                SourceLocation breakLoc = breakS->getBreakLoc();
                getRewriter().InsertTextAfterToken(breakLoc, " " + std::string(1, label-2));
            }
            else if (auto *contS = dyn_cast<ContinueStmt>(stmt)) {
                SourceLocation contLoc = contS->getContinueLoc();
                getRewriter().InsertTextAfterToken(contLoc, " " + std::string(1, label-3));
            }

            // Process nested statements
            for (Stmt *child : stmt->children()) {
                if (child) {
                    if (isa<ForStmt>(child) || isa<WhileStmt>(child) || 
                        isa<DoStmt>(child) || isa<SwitchStmt>(child)) {
                        std::string childLabels = "\n";
                        for (int i = 0; i < 3; i++) {
                            childLabels += std::string(1, label++) + ": ";
                        }
                        getRewriter().InsertTextBefore(child->getBeginLoc(), childLabels);
                    }
                    processStmt(child);
                }
            }
        };

        processStmt(S);
    // }
        return true;
    }

    bool VisitStmt(Stmt *S) {
        if (isa<ForStmt>(S) || isa<WhileStmt>(S) || 
            isa<DoStmt>(S) || isa<SwitchStmt>(S)) {
            Statements.push_back(S);
        }
        return true;
    }

private:
    std::vector<Stmt*> Statements;
};

static RegisterMutator<AddLabeledBreakContinue> M(
    "add-labeled-break-continue",
    "Adds labels to loops and switch statements and modifies break/continue statements to use labels"
);