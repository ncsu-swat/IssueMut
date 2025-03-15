#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class VectorTypedefModifier : public Mutator, 
    public RecursiveASTVisitor<VectorTypedefModifier> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetTypedefs.empty()) return false;
        
        TypedefDecl *Target = randElement(TargetTypedefs); // TargetTypedefs[0];
        SourceRange Range = Target->getSourceRange();
        
        std::string NewTypeStr = "int64_t";
        
        // Get source range of the underlying type
        TypeSourceInfo *TSI = Target->getTypeSourceInfo();
        SourceRange TypeRange = TSI->getTypeLoc().getSourceRange();
        
        getRewriter().ReplaceText(TypeRange, NewTypeStr);
        
        return true;
    }

    bool VisitTypedefDecl(TypedefDecl *D) {
        if (D->getUnderlyingType().getAsString().find("__int128") != std::string::npos) {
            TargetTypedefs.push_back(D);
        }
        return true;
    }

private:
    std::vector<TypedefDecl *> TargetTypedefs;
};

static RegisterMutator<VectorTypedefModifier> M(
    "vector.typedef.modifier",
    "Modifies vector typedef from __int128 to int64_t.");