#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ModifyBitField : public Mutator, public RecursiveASTVisitor<ModifyBitField> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (BitFields.empty()) return false;

        // Select the first bit-field declaration
        FieldDecl *BitField = randElement(BitFields); // BitFields[0];
        
        // Get the location of the bit-field width
        SourceLocation BitWidthLoc = BitField->getBitWidth()->getBeginLoc();
        
        // Replace the bit-field width with "1"
        getRewriter().ReplaceText(BitWidthLoc, 1, "1");
        
        return true;
    }

    bool VisitFieldDecl(FieldDecl *Decl) {
        if (Decl->isBitField()) {
            BitFields.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<FieldDecl *> BitFields;
};

static RegisterMutator<ModifyBitField> M(
    "ModifyBitField", 
    "Modifies a bit-field width from 2 to 1.");