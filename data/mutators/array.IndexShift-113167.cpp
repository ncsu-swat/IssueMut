#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ArrayIndexShiftMutator : public Mutator, public RecursiveASTVisitor<ArrayIndexShiftMutator> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (VarDecls.empty() && ForStmts.empty()) {
            return false;
        }

        // Modify array declaration
        // if (ArrayDecl) {
        VarDecl *ArrayDecl = randElement(VarDecls);
            if (auto *CAT = dyn_cast<ConstantArrayType>(ArrayDecl->getType()->getAsArrayTypeUnsafe())) {
                SourceLocation ArrSize = ArrayDecl->getLocation();
                // Find the location of '[N]' in the declaration
                ArrSize = Lexer::findLocationAfterToken(ArrSize, 
                    tok::l_square,
                    getRewriter().getSourceMgr(),
                    getASTContext().getLangOpts(),
                    /*SkipTrailingWhitespaceAndNewLine=*/true);
                
                if (ArrSize.isValid()) {
                    getRewriter().InsertTextAfterToken(ArrSize, "+1");
                }
            }
        // }

        // Modify for loops and array accesses
        // for (auto *ForStmt : ForStmts) {
        auto *ForStmt = randElement(ForStmts);
            // Get init, cond and inc expressions
            auto *Init = dyn_cast<BinaryOperator>(ForStmt->getInit());
            auto *Cond = dyn_cast<BinaryOperator>(ForStmt->getCond());
            
            if (Init && Cond) {
                // Change initialization to i = 1
                SourceRange InitRange = Init->getRHS()->getSourceRange();
                getRewriter().ReplaceText(InitRange, "1");

                // Change condition to i <= N 
                SourceRange OpRange = Cond->getOperatorLoc();
                getRewriter().ReplaceText(OpRange, "<=");
            }
        // }

        return true;
    }

    bool VisitVarDecl(VarDecl *Decl) {
        if (Decl->getType()->isArrayType()) {
            // ArrayDecl = Decl;
            VarDecls.push_back(Decl);
        }
        return true;
    }

    bool VisitForStmt(ForStmt *Stmt) {
        ForStmts.push_back(Stmt);
        return true;
    }

private:
    // VarDecl *ArrayDecl = nullptr;
    std::vector<VarDecl*> VarDecls;
    std::vector<ForStmt*> ForStmts;
};

static RegisterMutator<ArrayIndexShiftMutator> M(
    "array.IndexShift", 
    "Shifts array indexing to start from 1 instead of 0");