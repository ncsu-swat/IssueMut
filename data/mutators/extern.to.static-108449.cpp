#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ExternToStaticMutator : public Mutator, 
                             public RecursiveASTVisitor<ExternToStaticMutator> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (ExternDecls.empty()) return false;

        // Select a random extern declaration to modify
        DeclaratorDecl *TargetDecl = randElement(ExternDecls);
        
        SourceLocation ExternLoc = TargetDecl->getSourceRange().getBegin();
        
        // Replace 'extern' with 'static'
        getRewriter().ReplaceText(ExternLoc, 6, "static");
        
        return true;
    }

    bool VisitVarDecl(VarDecl *Decl) {
        if (Decl->getStorageClass() == SC_Extern && !Decl->isImplicit()) {
            ExternDecls.push_back(Decl);
        }
        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *Decl) {
        if (Decl->getStorageClass() == SC_Extern && !Decl->isImplicit()) {
            ExternDecls.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<DeclaratorDecl *> ExternDecls;
};

// static RegisterMutator<ExternToStaticMutator> M(
//     "extern.to.static",
//     "Replaces 'extern' storage class specifier with 'static'.");