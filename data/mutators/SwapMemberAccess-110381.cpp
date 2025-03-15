#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class SwapMemberAccess : public Mutator, 
    public RecursiveASTVisitor<SwapMemberAccess> {
public:
    using Mutator::Mutator;
    FunctionDecl* CurrentFunction = nullptr;

    bool mutate() override {
        TraverseAST(getASTContext());
        // if (TargetStatements.size() < 3) return false;
        if (TargetPairs.empty()) return false;

        std::pair<FunctionDecl*, std::vector<BinaryOperator*>> TargetPair = randElement(TargetPairs);
        FunctionDecl* FD = TargetPair.first;
        std::vector<BinaryOperator*> TargetStatements = TargetPair.second;

        // Get the source text of the three statements
        std::string stmt1 = getText(TargetStatements[0]);
        std::string stmt2 = getText(TargetStatements[1]);
        std::string stmt3 = getText(TargetStatements[2]);

        // Get the locations
        SourceLocation startLoc = TargetStatements[0]->getBeginLoc();
        SourceLocation endLoc = TargetStatements[2]->getEndLoc();

        // Create the replacement text with reordered statements
        std::string replacement = "\n      " + stmt1 + ";\n      " + 
                                stmt3 + ";\n      " + stmt2;

        // Replace the original statements with the reordered ones
        getRewriter().ReplaceText(
            SourceRange(startLoc, endLoc),
            replacement);

        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *FD) {
        CurrentFunction = FD;
        return true;
    }

    bool VisitCompoundStmt(CompoundStmt *CS) {
        // Look for the compound statement in sum_8_foos function
        if (CurrentFunction/* && CurrentFunction->getNameAsString() == "sum_8_foos"*/) {
            // Find the three sum += statements
            std::vector<BinaryOperator*> TargetBinaryOperators;
            for (auto *S : CS->body()) {
                if (auto *ES = dyn_cast<BinaryOperator>(S)) {
                    if (ES->getOpcode() == BO_AddAssign) {
                        // TargetStatements.push_back(ES);
                        TargetBinaryOperators.push_back(ES);
                    }
                }
            }

            if (TargetBinaryOperators.size() >= 3) {
                TargetPairs.push_back({CurrentFunction, TargetBinaryOperators});
            }
        }
        return true;
    }

private:
    // std::vector<BinaryOperator*> TargetStatements;
    std::vector<std::pair<FunctionDecl*, std::vector<BinaryOperator*>>> TargetPairs;

    std::string getText(BinaryOperator* stmt) {
        SourceLocation startLoc = stmt->getBeginLoc();
        SourceLocation endLoc = stmt->getEndLoc();
        return std::string(Lexer::getSourceText(
            CharSourceRange::getCharRange(startLoc, 
                Lexer::getLocForEndOfToken(endLoc, 0, 
                    getRewriter().getSourceMgr(),
                    getASTContext().getLangOpts())),
            getRewriter().getSourceMgr(),
            getASTContext().getLangOpts()));
    }
};

static RegisterMutator<SwapMemberAccess> M(
    "SwapMemberAccess",
    "Swaps the order of member access statements in sum_8_foos function.");