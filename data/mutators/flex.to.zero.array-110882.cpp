#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class FlexArrayToZeroArray : public Mutator, 
                           public RecursiveASTVisitor<FlexArrayToZeroArray> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (FlexArrayFields.empty()) return false;

        FieldDecl *Field = randElement(FlexArrayFields);
        
        const ArrayType *AT = Field->getType()->getAsArrayTypeUnsafe();
        if (!AT) return false;

        SourceRange TypeRange = Field->getTypeSourceInfo()->getTypeLoc().getSourceRange(); 
        std::string TypeStr = "int " + Field->getNameAsString() + "[0]";
        
        getRewriter().ReplaceText(TypeRange, TypeStr);
        
        return true;
    }

    bool VisitFieldDecl(FieldDecl *Field) {
        if (const ArrayType *AT = Field->getType()->getAsArrayTypeUnsafe()) {
            if (AT->isIncompleteArrayType()) {
                FlexArrayFields.push_back(Field);
            }
        }
        return true;
    }

private:
    std::vector<FieldDecl *> FlexArrayFields;
};

static RegisterMutator<FlexArrayToZeroArray> M(
    "flex.to.zero.array", 
    "Converts flexible array members to zero-length arrays");