#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class AddNoCalleeSavedRegisters : public Mutator, 
    public clang::RecursiveASTVisitor<AddNoCalleeSavedRegisters> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetFuncDecls.empty()) return false;

        // Select bar0 function declaration
        // FunctionDecl *FuncDecl = nullptr;
        // for (auto *Decl : TargetFuncDecls) {
        //     if (Decl->getNameAsString() == "bar0") {
        //         FuncDecl = Decl;
        //         break;
        //     }
        // }
        
        // if (!FuncDecl) return false;

        FunctionDecl *FuncDecl = randElement(TargetFuncDecls);

        // Insert attribute before semicolon
        SourceLocation EndLoc = FuncDecl->getSourceRange().getEnd();
        if (EndLoc.isInvalid()) return false;

        // Find semicolon after the declaration
        SourceLocation SemiLoc = Lexer::findLocationAfterToken(
            EndLoc,
            tok::semi,
            getRewriter().getSourceMgr(),
            getASTContext().getLangOpts(),
            false);

        if (SemiLoc.isInvalid()) return false;

        // Get location before semicolon
        SourceLocation InsertLoc = SemiLoc.getLocWithOffset(-1);

        // Insert attribute
        getRewriter().InsertText(
            InsertLoc,
            "\n   __attribute__ ((no_callee_saved_registers))"
        );

        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *Decl) {
        if (Decl->isExternC()) {
            TargetFuncDecls.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<FunctionDecl *> TargetFuncDecls;
};

static RegisterMutator<AddNoCalleeSavedRegisters> M(
    "add.nocalleesavedregisters", 
    "Adds no_callee_saved_registers attribute to bar0 function declaration."
);