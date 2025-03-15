#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ReplaceVarWithFuncCall : public Mutator, 
                              public RecursiveASTVisitor<ReplaceVarWithFuncCall> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        // if (!FoundVar || !FoundFunc) return false;
        if (FoundFuncs.empty() || VarRefs.empty()) return false;

        FunctionDecl* TargetFunc = randElement(FoundFuncs);
        DeclRefExpr* VarRef = randElement(VarRefs);

        SourceLocation VarLoc = VarRef->getBeginLoc();
        if (VarLoc.isInvalid()) return false;

        std::string text = TargetFunc->getNameAsString() + "()";

        // Replace variable reference with function call
        getRewriter().ReplaceText(VarRef->getSourceRange(), text);
        return true;
    }

    bool VisitDeclRefExpr(DeclRefExpr *E) {
        // if (VarDecl *VD = dyn_cast<VarDecl>(E->getDecl())) {
        //     if (VD->getName() == "s") {
        //         VarRef = E;
        //         FoundVar = true;
        //     }
        // }
        VarRefs.push_back(E);
        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *D) {
        // if (D->getName() == "f1") {
        //     FoundFunc = true;
        // }
        if (D->getNumParams() == 0) {
            FoundFuncs.push_back(D);
        }
        return true;
    }

private:
    // bool FoundVar = false;
    // bool FoundFunc = false;
    std::vector<FunctionDecl*> FoundFuncs;
    std::vector<DeclRefExpr*> VarRefs;
    // DeclRefExpr *VarRef = nullptr;
};

static RegisterMutator<ReplaceVarWithFuncCall> M(
    "ReplaceVarWithFuncCall", 
    "Replaces variable 's' with call to function 'f1()'");