#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeFunctionParamType : public Mutator, public clang::RecursiveASTVisitor<ChangeFunctionParamType> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetFunctions.empty()) return false;

        // Select a random function declaration to modify
        FunctionDecl *FuncDecl = randElement(TargetFunctions);
        
        // Prepare to mutate parameter type
        if (FuncDecl->param_size() == 0) {
            return false; // The function has no parameters, cannot mutate.
        }
        
        ParmVarDecl *ParamDecl = FuncDecl->getParamDecl(randIndex(FuncDecl->param_size())); // Get the first parameter
        if (!ParamDecl) return false;

        // Get source location for the parameter type
        SourceLocation ParamLoc = ParamDecl->getSourceRange().getBegin();
        std::string NewType = "char ";

        // Replace the parameter type
        getRewriter().ReplaceText(ParamLoc, ParamDecl->getType().getAsString().length(), NewType);
        
        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *Decl) {
        // Check if the declaration is the target function
        if (/*Decl->getName() == "FOO_showfatal" && */!Decl->isImplicit()) {
            TargetFunctions.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<FunctionDecl *> TargetFunctions;
};

// Register the mutator
static RegisterMutator<ChangeFunctionParamType> M(
    "ChangeFunctionParamType",
    "Changes the first parameter of function 'FOO_showfatal' from 'int' to 'char'.");