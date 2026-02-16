#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class AddFunctionPointerMutator : public Mutator, 
    public RecursiveASTVisitor<AddFunctionPointerMutator> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (Targets.empty()) return false;

        auto *Target = randElement(Targets);
        SourceLocation Loc = Target->getLocation();
        
        // Find the location after the identifier
        SourceLocation AfterIdLoc = Lexer::getLocForEndOfToken(
            Loc, 0, getRewriter().getSourceMgr(), 
            getASTContext().getLangOpts());
        
        if (AfterIdLoc.isInvalid()) return false;
        
        // Insert "()" after the identifier
        getRewriter().InsertText(AfterIdLoc, "()");
        
        return true;
    }

    bool VisitDecl(Decl *D) {
        if (auto *VD = dyn_cast<VarDecl>(D)) {
            if (VD->getType()->isPointerType()) {
                QualType PointeeType = VD->getType()->getPointeeType();
                if (PointeeType->isArrayType()) {
                    Targets.push_back(VD);
                }
            }
        }
        else if (auto *PVD = dyn_cast<ParmVarDecl>(D)) {
            if (PVD->getType()->isPointerType()) {
                QualType PointeeType = PVD->getType()->getPointeeType();
                if (PointeeType->isArrayType()) {
                    Targets.push_back(PVD);
                }
            }
        }
        return true;
    }

private:
    std::vector<NamedDecl*> Targets;
};

static RegisterMutator<AddFunctionPointerMutator> M(
    "add.function.pointer",
    "Converts array pointer parameters to function pointer parameters.");