#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class UnsignedToSignedCharMutator : public Mutator,
    public RecursiveASTVisitor<UnsignedToSignedCharMutator> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (UnsignedCharVars.empty()) return false;

        VarDecl *VarToMutate = randElement(UnsignedCharVars);
        
        SourceLocation TypeLoc = VarToMutate->getTypeSourceInfo()
            ->getTypeLoc().getBeginLoc();
        
        if (TypeLoc.isInvalid()) return false;

        getRewriter().ReplaceText(
            SourceRange(TypeLoc, TypeLoc.getLocWithOffset(strlen("unsigned"))), 
            "");

        return true;
    }

    bool VisitVarDecl(VarDecl *Decl) {
        QualType T = Decl->getType();
        const Type* TypePtr = T.getTypePtr();
        if (TypePtr->isCharType() && TypePtr->isUnsignedIntegerType()) {
            UnsignedCharVars.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<VarDecl *> UnsignedCharVars;
};

static RegisterMutator<UnsignedToSignedCharMutator> M(
    "UnsignedToSignedChar.114965", 
    "Changes unsigned char type to char type.");