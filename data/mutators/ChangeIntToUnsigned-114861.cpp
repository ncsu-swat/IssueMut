#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeIntToUnsigned : public Mutator, public RecursiveASTVisitor<ChangeIntToUnsigned> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (IntVarDecls.empty())
            return false;

        // Select a random 'int' variable declaration to modify
        VarDecl *VD = randElement(IntVarDecls);

        // Get the source range of the type specifier in the variable declaration
        TypeSourceInfo *TSI = VD->getTypeSourceInfo();
        if (!TSI)
            return false;

        TypeLoc TL = TSI->getTypeLoc();
        SourceRange TypeRange = TL.getSourceRange();
        if (TypeRange.isInvalid())
            return false;

        // Get the full source range, including any typedefs or elaborated types
        SourceRange FullTypeRange = getExpansionRange(TypeRange);

        // Replace the type specifier with 'unsigned'
        std::string NewType = "unsigned";
        getRewriter().ReplaceText(FullTypeRange, NewType);

        return true;
    }

    bool VisitVarDecl(VarDecl *VD) {
        // Skip implicit declarations and parameters
        if (VD->isImplicit() || isa<ParmVarDecl>(VD))
            return true;

        // Check if the variable is of type 'int' (excluding other integer types)
        QualType QT = VD->getType();
        if (QT->isSpecificBuiltinType(BuiltinType::Int)) {
            IntVarDecls.push_back(VD);
        }

        return true;
    }

private:
    std::vector<VarDecl *> IntVarDecls;
};

// Register the mutator
static RegisterMutator<ChangeIntToUnsigned> M(
    "ChangeIntToUnsigned",
    "Changes the type of a randomly selected 'int' variable to 'unsigned'.");