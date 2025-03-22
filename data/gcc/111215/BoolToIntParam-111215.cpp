#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class BoolToIntParamMutator : public Mutator, public RecursiveASTVisitor<BoolToIntParamMutator> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetFunctions.empty()) return false;

        // Select function 'f'
        // for (FunctionDecl *FD : TargetFunctions) {
        //     if (FD->getNameAsString() == "f") {
                FunctionDecl *FD = randElement(TargetFunctions);
                // Get parameter locations
                for (unsigned i = 0; i < FD->getNumParams(); i++) {
                    ParmVarDecl *PVD = FD->getParamDecl(i);
                    QualType ParamType = PVD->getType();
                    
                    if (ParamType->isBooleanType()) {
                        SourceRange TypeRange = PVD->getTypeSourceInfo()->getTypeLoc().getSourceRange();
                        getRewriter().ReplaceText(TypeRange, "int");
                    }
                }
        //         break;
        //     }
        // }
        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *Decl) {
        if (!Decl->isImplicit()) {
            TargetFunctions.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<FunctionDecl *> TargetFunctions;
};

static RegisterMutator<BoolToIntParamMutator> M(
    "BoolToIntParam",
    "Changes _Bool parameters to int in function f");