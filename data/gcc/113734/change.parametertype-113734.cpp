#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeParameterType113734 : public Mutator, 
                          public RecursiveASTVisitor<ChangeParameterType113734> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetParams.empty()) return false;

        auto *TargetParam = randElement(TargetParams);
        SourceLocation TypeLoc = TargetParam->getTypeSourceInfo()->getTypeLoc().getBeginLoc();
        getRewriter().ReplaceText(TypeLoc, strlen("unsigned int"), "unsigned short");
        
        return true;
    }

    bool VisitParmVarDecl(ParmVarDecl *Param) {
        if (Param->getType().getAsString() == "unsigned int") {
            TargetParams.push_back(Param);
        }
        return true;
    }

private:
    std::vector<ParmVarDecl *> TargetParams;
};

static RegisterMutator<ChangeParameterType113734> M(
    "change.parametertype", 
    "Changes parameter type from 'unsigned int' to 'unsigned short'");