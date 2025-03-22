#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeRegisterType : public Mutator, public clang::RecursiveASTVisitor<ChangeRegisterType> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        return !TargetVarDecls.empty() && applyMutations();
    }

    bool VisitVarDecl(VarDecl *Decl) {
        // Check if the declaration is a registered variable with the name 'd'
        if (Decl->hasLocalStorage()/* && Decl->getName() == "d"*/ && 
            Decl->getType()->isSignedIntegerType()) {
            // This assumes 'long' is the specific type for the variable
            if (Decl->getType()->getAs<BuiltinType>() &&
                Decl->getType()->getAs<BuiltinType>()->getKind() == BuiltinType::Long) {
                TargetVarDecls.push_back(Decl);
            }
        }
        return true;
    }

private:
    std::vector<VarDecl *> TargetVarDecls;

    bool applyMutations() {
        // Select the first found variable declaration to mutate
        VarDecl *VarDeclToMutate = randElement(TargetVarDecls); //TargetVarDecls[0];
        
        // Get the location of the variable type
        SourceLocation TypeLoc = VarDeclToMutate->getTypeSpecStartLoc();
        if (TypeLoc.isInvalid()) return false;

        // Prepare the new type as a string
        std::string NewType = "long long ";
        
        // Replace the variable declaration type with the new type
        getRewriter().ReplaceText(TypeLoc, 5, NewType); // Replacing 'long' with 'long long'
        
        return true;
    }
};

// Register the mutator
static RegisterMutator<ChangeRegisterType> M(
    "ChangeRegisterType",
    "Changes 'register long' to 'register long long' for variable 'd'.");