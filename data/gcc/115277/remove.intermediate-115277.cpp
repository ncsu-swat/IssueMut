#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveIntermediate : public Mutator, public RecursiveASTVisitor<RemoveIntermediate> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (Targets.empty()) return false;

        // for (auto& Target : Targets) {
        auto& Target = randElement(Targets);
        
            // Get the VarDecl source range
            SourceRange VarDeclRange = Target->getSourceRange();
            
            // Get the complete statement including semicolon
            SourceLocation SemiLoc = Lexer::findNextToken(VarDeclRange.getEnd(), 
                getRewriter().getSourceMgr(),
                getASTContext().getLangOpts())->getLocation();
            
            // Remove the variable declaration including semicolon
            getRewriter().RemoveText(SourceRange(VarDeclRange.getBegin(), SemiLoc));
            
            // Get the initialization expression
            Expr* InitExpr = Target->getInit();
            
            // Find and replace all references in the loop
            for (auto& UseRef : VarRefs[Target]) {
                // Replace each reference with the original initialization expression
                std::string InitStr = getText(InitExpr->getSourceRange());
                getRewriter().ReplaceText(UseRef->getSourceRange(), InitStr);
            }
        // }
        
        return true;
    }

    bool VisitVarDecl(VarDecl *Decl) {
        if (!Decl->hasInit()) return true;
        
        // Look for local variables named 'limit'
        if (/* Decl->getName() == "limit" && */Decl->isLocalVarDecl()) {
            Targets.push_back(Decl);
        }
        return true;
    }
    
    bool VisitDeclRefExpr(DeclRefExpr *Ref) {
        if (const VarDecl *VD = dyn_cast<VarDecl>(Ref->getDecl())) {
            // if (VD->getName() == "limit") {
                VarRefs[VD].push_back(Ref);
            // }
        }
        return true;
    }

private:
    std::vector<VarDecl*> Targets;
    std::map<const VarDecl*, std::vector<DeclRefExpr*>> VarRefs;
    
    std::string getText(SourceRange Range) {
        return Lexer::getSourceText(CharSourceRange::getTokenRange(Range),
                                  getRewriter().getSourceMgr(),
                                  getASTContext().getLangOpts()).str();
    }
};

static RegisterMutator<RemoveIntermediate> M(
    "remove.intermediate", 
    "Removes intermediate variable declarations and replaces uses with original expression");