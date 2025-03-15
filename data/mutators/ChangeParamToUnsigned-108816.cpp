#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeParamToUnsigned : public Mutator, public RecursiveASTVisitor<ChangeParamToUnsigned> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (IntParams.empty()) return false;

        // Select a random int parameter to modify
        ParmVarDecl *Param = randElement(IntParams);
        
        SourceLocation TypeLoc = Param->getTypeSourceInfo()->getTypeLoc().getBeginLoc();
        
        // Replace 'int' with 'unsigned int'
        getRewriter().ReplaceText(TypeLoc, 3, "unsigned int");

        return true;
    }

    bool VisitParmVarDecl(ParmVarDecl *Param) {
        if (Param->getType().getCanonicalType().getAsString() == "int") {
            IntParams.push_back(Param);
        }
        return true;
    }

private:
    std::vector<ParmVarDecl *> IntParams;
};

static RegisterMutator<ChangeParamToUnsigned> M(
    "ChangeParamToUnsigned", 
    "Changes an integer parameter to unsigned integer.");