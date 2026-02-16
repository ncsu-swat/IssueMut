#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class AddBitIntDecl : public Mutator, public RecursiveASTVisitor<AddBitIntDecl> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetFuncs.empty()) return false;

        // Select function to modify
        FunctionDecl *FuncDecl = randElement(TargetFuncs); // TargetFuncs[0];
        
        CompoundStmt *Body = dyn_cast<CompoundStmt>(FuncDecl->getBody());
        if (!Body || Body->body_empty()) return false;

        // Get location after first {
        SourceLocation InsertLoc = Body->getLBracLoc().getLocWithOffset(1);

        ParmVarDecl *param = FuncDecl->getParamDecl(randIndex(FuncDecl->getNumParams()));
        
        std::string NewDecl = "\n  signed char c = *(_BitInt(128) *) " + param->getNameAsString() + ";\n";
        getRewriter().InsertTextAfterToken(InsertLoc, NewDecl);

        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *Decl) {
        if (Decl->getNumParams() != 0) {
            TargetFuncs.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<FunctionDecl *> TargetFuncs;
};

static RegisterMutator<AddBitIntDecl> M(
    "add.bitint.decl", 
    "Adds a _BitInt declaration at the start of function foo");