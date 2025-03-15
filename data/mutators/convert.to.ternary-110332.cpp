#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ConvertToTernaryMutator : public Mutator, 
    public RecursiveASTVisitor<ConvertToTernaryMutator> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetFuncs.empty() || TargetBoolVars.empty() || TargetUnsignedVars.size() < 2) return false;

        FunctionDecl* FD = randElement(TargetFuncs);

        // Modify return type to reference
        SourceLocation RetLoc = FD->getReturnTypeSourceRange().getBegin();
        getRewriter().InsertTextAfterToken(RetLoc, "&");

        std::vector<ReturnStmt*> ReturnStmts;
        if (CompoundStmt *Body = dyn_cast<CompoundStmt>(FD->getBody())) {
            for (auto *S : Body->body()) {
                if (ReturnStmt *Ret = dyn_cast<ReturnStmt>(S)) {
                    ReturnStmts.push_back(Ret);
                }
            }
        }

        if (ReturnStmts.empty()) return false;

        ReturnStmt* RS = randElement(ReturnStmts);
        VarDecl* b4 = randElement(TargetBoolVars);
        VarDecl* u6 = randElement(TargetUnsignedVars);
        VarDecl* u9 = randElement(TargetUnsignedVars);
        Expr* RetVal = RS->getRetValue();
        std::string NewStatement = "return " + b4->getNameAsString() + " ? " + u6->getNameAsString() + " : " + u9->getNameAsString();
        getRewriter().ReplaceText(RS->getSourceRange(), NewStatement);

        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *FD) {
        if (!FD->isImplicit()) {
            QualType RetType = FD->getReturnType();
            CompoundStmt* Body = dyn_cast<CompoundStmt>(FD->getBody());
            if (RetType->isUnsignedIntegerType() && Body) {
                TargetFuncs.push_back(FD);
            }
        }
        return true;
    }

    bool VisitVarDecl(VarDecl *VD) {
        if (VD->isFileVarDecl()) {
            if (VD->getType()->isUnsignedIntegerType()) {
                TargetUnsignedVars.push_back(VD);
            } else if (VD->getType()->isIntegerType()) {
                TargetBoolVars.push_back(VD);
            }
        }
        return true;
    }

private:
    std::vector<FunctionDecl*> TargetFuncs;
    std::vector<VarDecl*> TargetUnsignedVars;
    std::vector<VarDecl*> TargetBoolVars;
};

static RegisterMutator<ConvertToTernaryMutator> M(
    "convert.to.ternary", 
    "Converts if-return to ternary expression and modifies function.");