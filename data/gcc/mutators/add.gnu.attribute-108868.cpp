#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class AddGNUAttribute : public Mutator, public RecursiveASTVisitor<AddGNUAttribute> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        // if (!Target) return false;
        if (TargetFuncDecls.empty()) return false;

        FunctionDecl *Target = randElement(TargetFuncDecls);
        for (const Attr *A : Target->attrs()) {
            if (isa<LeafAttr>(A)) {
                SourceLocation Loc = A->getRange().getEnd();
                SourceLocation InsertLoc = Lexer::getLocForEndOfToken(
                    Loc, 0, getRewriter().getSourceMgr(), 
                    getASTContext().getLangOpts());
                
                getRewriter().InsertTextAfter(InsertLoc, ", __returns_twice__");
                return true;
            }
        }

        return false;
    }

    bool VisitFunctionDecl(FunctionDecl *Decl) {
        if (
            // Decl->getNameAsString() == "vfork" && 
            !Decl->isImplicit() &&
            Decl->hasAttr<LeafAttr>()) {
            // Target = Decl;
            TargetFuncDecls.push_back(Decl);
        }
        return true;
    }

private:
    // FunctionDecl *Target = nullptr;
    std::vector<FunctionDecl *> TargetFuncDecls;
};

static RegisterMutator<AddGNUAttribute> M(
    "add.gnu.attribute", 
    "Adds __returns_twice__ attribute to vfork function declaration.");