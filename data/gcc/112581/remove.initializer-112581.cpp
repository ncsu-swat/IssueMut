#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveInitializer112581 : public Mutator, public RecursiveASTVisitor<RemoveInitializer112581> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (DeclsWithInit.empty()) return false;

        // for (VarDecl *Decl : DeclsWithInit) {
            VarDecl *Decl = randElement(DeclsWithInit);
            if (Decl->hasInit()) {
                SourceRange InitRange = Decl->getInit()->getSourceRange();
                SourceLocation StartLoc = Lexer::getLocForEndOfToken(
                    Decl->getLocation(), 0, 
                    getSourceManager(),
                    getASTContext().getLangOpts());
                
                // Remove initializer including equals sign
                getRewriter().RemoveText(
                    SourceRange(StartLoc, InitRange.getEnd()));
            }
        // }
        
        return true;
    }

    bool VisitVarDecl(VarDecl *Decl) {
        if (Decl->hasInit() && !Decl->isImplicit() && 
            getSourceManager().isInMainFile(Decl->getLocation())/* &&
            (Decl->getName() == "h" || Decl->getName() == "i")*/) {
            DeclsWithInit.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<VarDecl *> DeclsWithInit;
};

static RegisterMutator<RemoveInitializer112581> M(
    "remove.initializer.112581", 
    "Removes initializer from variable declarations.");
