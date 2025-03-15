#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeParameterType : public Mutator, public clang::RecursiveASTVisitor<ChangeParameterType> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        
        // If we found applicable functions, perform the mutation.
        for (auto *Decl : TargetFunctions) {
            auto Params = Decl->parameters();
            if (Params.size() > 0) { // Ensure there is one parameter
                ParmVarDecl *Param = Params[randIndex(Params.size())];

                // Check if the old type is 'int' before changing
                if (Param->getType()->isIntegerType()) {
                    // Prepare to change the type to 'char'
                    QualType NewType = getASTContext().CharTy;

                    // Get the source range for the parameter's type
                    SourceLocation StartLoc = Param->getTypeSourceInfo()->getTypeLoc().getBeginLoc();
                    SourceLocation EndLoc = Param->getTypeSourceInfo()->getTypeLoc().getEndLoc();

                    // Replace the old type with the new type in the function declaration
                    getRewriter().ReplaceText(SourceRange(StartLoc, EndLoc), NewType.getAsString());

                    return true; // Return true to indicate a mutation was made
                }
            }
        }

        return false; // No mutation was made
    }

    bool VisitFunctionDecl(FunctionDecl *Decl) {
        // Check the function name and ensure it's not implicit
        if (/*Decl->getName() == "FOO_showfatal" && */!Decl->isImplicit()) {
            TargetFunctions.push_back(Decl); // Collect the target function
        }
        return true; // Continue traversing
    }

private:
    std::vector<FunctionDecl *> TargetFunctions; // List of target functions to mutate
};

// Register the mutator
static RegisterMutator<ChangeParameterType> M(
    "ChangeParameterType",
    "Changes the parameter type of FOO_showfatal from int to char.");