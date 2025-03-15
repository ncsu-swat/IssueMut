#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h" 
#include "MutatorManager.h"

using namespace clang;

class ModifyBitwiseReturn : public Mutator, public RecursiveASTVisitor<ModifyBitwiseReturn> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());

        if (ReturnTriples.empty()) return false;

        const auto &triple = randElement(ReturnTriples);

        
        Expr *RetVal = triple.ReturnExpr;
        ParmVarDecl *firstParam = triple.FirstParam;
        ParmVarDecl *secondParam = triple.SecondParam;        

        std::string paramName = firstParam->getNameAsString();
        std::string returnVar = getText(RetVal);
        QualType secondParamType = secondParam->getType();
        
        bool isBool = secondParamType->isBooleanType();
        
        std::string replacement;
        if (isBool) {
            replacement = "(" + returnVar + " & (" + 
                        paramName + "|7))";
        } else {
            replacement = "(" + returnVar + " & (" + 
                        paramName + "|3))";
        }
        
        SourceRange SR = RetVal->getSourceRange();
        getRewriter().ReplaceText(SR, replacement);
        
        // return modified;
        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *FD) {
        if (!FD->hasBody()) return true;
        
        CompoundStmt *Body = dyn_cast<CompoundStmt>(FD->getBody());
        if (!Body) return true;

        for (auto *Stmt : Body->body()) {
            if (ReturnStmt *RS = dyn_cast<ReturnStmt>(Stmt)) {
                if (Expr *RetVal = RS->getRetValue()) {
                    
                    ParmVarDecl *firstParam = nullptr;
                    ParmVarDecl *secondParam = nullptr;
                    if (FD->param_size() > 1) {
                        firstParam = FD->getParamDecl(0);
                        secondParam = FD->getParamDecl(1);
                    }
                    
                    if (firstParam && secondParam) {
                        ReturnTriples.push_back({RetVal, firstParam, secondParam});
                    }
                }
            }
        }
        return true;
    }

private:
    // bool modified = false;
    struct ReturnTriple {
        Expr *ReturnExpr;
        ParmVarDecl *FirstParam;
        ParmVarDecl *SecondParam;
    };
    std::vector<ReturnTriple> ReturnTriples;

    std::string getText(const Stmt *stmt) {
        SourceRange SR = stmt->getSourceRange();
        return std::string(Lexer::getSourceText(
            CharSourceRange::getTokenRange(SR),
            getRewriter().getSourceMgr(), 
            getASTContext().getLangOpts()));
    }
};

static RegisterMutator<ModifyBitwiseReturn> 
X("modify.bitwise.return", "Modifies return statements with bitwise operations.");