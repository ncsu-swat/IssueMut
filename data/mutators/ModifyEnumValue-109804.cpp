#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ModifyEnumValue : public Mutator, public clang::RecursiveASTVisitor<ModifyEnumValue> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        return !EnumConstantDecls.empty() ? modifyEnumValue() : false;
    }

    bool VisitEnumDecl(EnumDecl *Decl) {
        for (auto *EnumConstant : Decl->enumerators()) {
            EnumConstantDecls.push_back(EnumConstant);
        }
        return true;
    }

private:

    std::vector<EnumConstantDecl *> EnumConstantDecls;

    bool modifyEnumValue() {
        
        EnumConstantDecl *EnumConstant = randElement(EnumConstantDecls);

        // Get the location of the enumerator
        SourceLocation StartLoc = EnumConstant->getBeginLoc();
        SourceLocation EndLoc = EnumConstant->getEndLoc();

        // Create the new value text
        std::string NewValue = EnumConstant->getNameAsString() + " = 1";

        // Insert the new value where ENUM_B is declared
        getRewriter().ReplaceText(SourceRange(StartLoc, EndLoc), NewValue);
        return true; // Successfully modified
    }
};

// Register the mutator
static RegisterMutator<ModifyEnumValue> M(
    "ModifyEnumValue",
    "Modifies the value of ENUM_B to be 1.");