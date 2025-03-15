#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class AddAttributeNoipa : public Mutator, public clang::RecursiveASTVisitor<AddAttributeNoipa> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetFunctions.empty())
            return false;

        // Select a random function declaration to modify
        FunctionDecl *FuncDecl = randElement(TargetFunctions);
        
        // Get the location of the function declaration
        SourceLocation Loc = FuncDecl->getLocation();
        if (Loc.isInvalid()) {
            return false;
        }

        // Prepare the new attribute string
        std::string NewAttribute = "__attribute__ ((noipa)) ";
        getRewriter().InsertText(Loc, NewAttribute, true, true);

        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *Decl) {
        // Target only non-member functions that are not implicit and are not inlined
        if (Decl->hasBody() && !Decl->isImplicit() && !Decl->isInlined()) {
            TargetFunctions.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<FunctionDecl *> TargetFunctions;
};

// Register the mutator
static RegisterMutator<AddAttributeNoipa> M(
    "AddAttributeNoipa",
    "Adds the __attribute__ ((noipa)) to randomly selected functions.");