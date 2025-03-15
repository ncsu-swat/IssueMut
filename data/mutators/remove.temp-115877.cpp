#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class SimplifyTempVariable : public Mutator, public RecursiveASTVisitor<SimplifyTempVariable> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        // if (!TempVarStmt || !AssignStmt) return false;
        if (Targets.empty()) return false;

        std::pair<std::string, BinaryOperator*> Target = randElement(Targets);
        std::string TempVarName = Target.first;
        BinaryOperator* AssignStmt = Target.second;

        VarDecl *VD = nullptr;
        for (auto TempVarDecl : TempVarDecls) {
            if (TempVarDecl->getNameAsString() == TempVarName) {
                VD = TempVarDecl;
                break;
            }
        }

        // Get the initializer expression of temp variable
        // DeclStmt *DS = cast<DeclStmt>(TempVarStmt);
        // VarDecl *VD = cast<VarDecl>(DS->getSingleDecl());
        Expr *Init = VD->getInit();

        // Get source text for the initializer
        std::string InitStr = getText(Init);

        // Get type of temp variable 
        std::string TypeStr = VD->getType().getAsString();

        // Replace i -= (int)temp with i -= (unsigned short)~u
        // SourceRange SR = AssignStmt->getSourceRange();
        // std::string Replacement = "i -= (" + TypeStr + ") " + InitStr;
        // getRewriter().ReplaceText(SR, Replacement);

        SourceRange SR = AssignStmt->getRHS()->getSourceRange();
        std::string Replacement = "(" + TypeStr + ") " + InitStr;
        getRewriter().ReplaceText(SR, Replacement);

        // Remove temp variable declaration
        SourceLocation EndLoc = Lexer::getLocForEndOfToken(
                    VD->getSourceRange().getEnd(), 0, getRewriter().getSourceMgr(),
                    getASTContext().getLangOpts());
        getRewriter().RemoveText(SourceRange(VD->getSourceRange().getBegin(), EndLoc));

        return true;
    }

    bool VisitDeclStmt(DeclStmt *S) {
        if (VarDecl *VD = dyn_cast<VarDecl>(S->getSingleDecl())) {
            // if (VD->getName() == "temp") {
            //     TempVarStmt = S;
            // }
            TempVarDecls.push_back(VD);
            TempVarNames.push_back(VD->getNameAsString());
        }
        return true;
    }

    bool VisitBinaryOperator(BinaryOperator *B) {
        if (B->getOpcode() == BO_SubAssign) {
            // AssignStmt = B;
            std::string exprStr = getText(B->getSourceRange());
            
            for (auto name : TempVarNames) {
                if (exprStr.find(name) != std::string::npos) {
                    Targets.push_back({name, B});
                    break;
                }
            }
        }
        return true;
    }

private:
    // Stmt *TempVarStmt = nullptr;
    // BinaryOperator *AssignStmt = nullptr;
    std::vector<VarDecl*> TempVarDecls;
    std::vector<std::string> TempVarNames;
    std::vector<std::pair<std::string, BinaryOperator*>> Targets;

    std::string getText(SourceRange SR) {
        return Lexer::getSourceText(
            CharSourceRange::getTokenRange(SR),
            getRewriter().getSourceMgr(),
            getASTContext().getLangOpts()).str();
    }

    std::string getText(Expr *E) {
        return getText(E->getSourceRange());
    }
};

static RegisterMutator<SimplifyTempVariable> M(
    "remove.temp",
    "Removes temporary variable and simplifies the expression.");