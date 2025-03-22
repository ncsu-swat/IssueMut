#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ReduceLoopUpperBound : public Mutator, public RecursiveASTVisitor<ReduceLoopUpperBound> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        return !Targets.empty() && applyMutation();
    }

    bool VisitFunctionDecl(FunctionDecl *Decl) {
        // Find the main function
        if (Decl->isMain() && Decl->hasBody()) {
            Targets.push_back(Decl);
        }
        return true;
    }

    bool VisitForStmt(ForStmt *For) {
        if (Targets.empty()) return true; // Only deal with main function

        // Example condition: n <= 3
        auto *Condition = For->getCond();
        if (Condition) {
            // Look for the pattern in the condition where the upper bound is a constant
            if (auto *BO = dyn_cast<BinaryOperator>(Condition)) {
                if (BO->getOpcode() == BO_LE && 
                    isa<IntegerLiteral>(BO->getRHS())) {
                    auto *IntLit = dyn_cast<IntegerLiteral>(BO->getRHS());
                    if (IntLit /* && IntLit->getValue() == 3 */) {
                        SourceLocation StartLoc = Condition->getBeginLoc();
                        SourceLocation EndLoc = Condition->getEndLoc();

                        std::string ConditionString = getText(SourceRange(StartLoc, EndLoc));
                        size_t pos = ConditionString.find("<=");

                        // If a space is found, remove everything after it
                        if (pos != std::string::npos) {
                            ConditionString = ConditionString.substr(0, pos); // Keep only the part before the space
                        }
                        
                        // Define the new condition
                        std::string NewCondition = ConditionString +"<= 2";
                        
                        // Replace the existing condition
                        // This replaces the entire condition with the new one
                        getRewriter().ReplaceText(SourceRange(StartLoc, 
                                                              EndLoc), NewCondition);
                        return false; // Don't visit inner nodes as the required mutation is done
                    }
                }
            }
        }
        return true;
    }

private:
    std::vector<FunctionDecl *> Targets;

    bool applyMutation() {
        // Call the Visitor, this will cause mutations for the functions visited
        TraverseAST(getASTContext());
        return true;
    }
    std::string getText(SourceRange Range) {
        return Lexer::getSourceText(
            CharSourceRange::getTokenRange(Range),
            getASTContext().getSourceManager(),
            getASTContext().getLangOpts()).str();
    }
};

// Register the mutator
static RegisterMutator<ReduceLoopUpperBound> M(
    "ReduceLoopUpperBound",
    "Reduces the upper bound of the loop in the main function from 3 to 2.");