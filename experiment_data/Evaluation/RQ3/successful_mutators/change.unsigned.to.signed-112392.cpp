#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeUnsignedToSigned : public Mutator, 
    public RecursiveASTVisitor<ChangeUnsignedToSigned> {

public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        // return !TargetVars.empty();
        if (TargetVars.empty()) return false;

        VarDecl* Target = randElement(TargetVars);

        SourceLocation TypeLoc = Target->getTypeSourceInfo()
            ->getTypeLoc().getBeginLoc();
        SourceLocation TypeEnd = Target->getTypeSourceInfo()
            ->getTypeLoc().getEndLoc();
        
        getRewriter().ReplaceText(
            SourceRange(TypeLoc, TypeEnd), 
            "int");

        return true;
    }

    bool VisitVarDecl(VarDecl *VD) {
        // if (VD->getName() == "absb") {
            QualType T = VD->getType();
            if (T->isUnsignedIntegerType()) {
                // SourceLocation TypeLoc = VD->getTypeSourceInfo()
                //     ->getTypeLoc().getBeginLoc();
                // SourceLocation TypeEnd = VD->getTypeSourceInfo()
                //     ->getTypeLoc().getEndLoc();
                
                // getRewriter().ReplaceText(
                //     SourceRange(TypeLoc, TypeEnd), 
                //     "int");
                    
                TargetVars.push_back(VD);
            }
        // }
        return true;
    }

private:
    std::vector<VarDecl*> TargetVars;
};

static RegisterMutator<ChangeUnsignedToSigned> M(
    "change.unsigned.to.signed",
    "Changes unsigned int to int for variable declarations.");