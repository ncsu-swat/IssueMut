#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveArrayInitializer : public Mutator, public RecursiveASTVisitor<RemoveArrayInitializer> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetDecls.empty()) return false;

        VarDecl *Decl = randElement(TargetDecls);
        SourceRange InitRange = Decl->getInit()->getSourceRange();
        
        // Remove the initializer and the equals sign
        getRewriter().RemoveText(SourceRange(
            InitRange.getBegin().getLocWithOffset(-2), 
            InitRange.getEnd()));

        return true;
    }

    bool VisitVarDecl(VarDecl *Decl) {
        if (Decl->hasInit() && Decl->getType()->isArrayType() && !Decl->isImplicit()) {
            TargetDecls.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<VarDecl *> TargetDecls;
};

static RegisterMutator<RemoveArrayInitializer> M(
    "remove.ArrayInitializer",
    "Removes the initializer from an array declaration."
);