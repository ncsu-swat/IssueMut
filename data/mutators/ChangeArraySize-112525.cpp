#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeArraySize : public Mutator, public clang::RecursiveASTVisitor<ChangeArraySize> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetFields.empty()) return false;

        // Select a random field declaration to modify
        FieldDecl *FieldDecl = randElement(TargetFields);

        // Find the location to modify the array size
        SourceLocation StartLoc = FieldDecl->getSourceRange().getEnd();
        SourceManager &SM = getRewriter().getSourceMgr();
        if (StartLoc.isInvalid())
            return false;

        // Find the end of the array size part
        SourceLocation SizeLoc = StartLoc.getLocWithOffset(-2); // Assuming array size is a constant before the closing bracket
        getRewriter().ReplaceText(SizeLoc, 2, std::to_string(getManager().randint(10, 99))); // Replace '14' with '15'

        return true;
    }

    bool VisitFieldDecl(FieldDecl *Decl) {
        // Check if the field is an array
        if (Decl->getType()->isVariableArrayType())
            return true; // Skip variable length arrays

        if (Decl->getType()->isConstantArrayType()) {
            const ConstantArrayType *ArrayType = 
                dyn_cast<ConstantArrayType>(Decl->getType().getCanonicalType());
            if (ArrayType && ArrayType->getSize().getZExtValue()/* == 14*/) {
                TargetFields.push_back(Decl);
            }
        }
        return true;
    }

private:
    std::vector<FieldDecl *> TargetFields;
};

// Register the mutator
static RegisterMutator<ChangeArraySize> M(
    "ChangeArraySize",
    "Increases the size of array 'arr' in struct 'teststruct' from 14 to 15.");