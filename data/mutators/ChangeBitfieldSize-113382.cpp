#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeBitfieldSize : public Mutator, public clang::RecursiveASTVisitor<ChangeBitfieldSize> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetBitfields.empty()) return false;

        // Select a random bitfield declaration to modify
        FieldDecl *BitfieldDecl = randElement(TargetBitfields);
        
        // Get the location of the bitfield declaration
        SourceLocation DeclLoc = BitfieldDecl->getSourceRange().getBegin();
        SourceLocation EndLoc = BitfieldDecl->getSourceRange().getEnd();

        // Create the new bitfield declaration
        // std::string NewBitfield = "enum foo f : 2";

        std::string BitfieldString = getText(SourceRange(DeclLoc, EndLoc));

        // Find the first space in the string
        size_t pos = BitfieldString.find(':');

        // If a space is found, remove everything after it
        if (pos != std::string::npos) {
            BitfieldString = BitfieldString.substr(0, pos); // Keep only the part before the space
        }

        std::string NewBitfield = BitfieldString + ": 2";

        // Insert the new declaration at the correct position (before the old bitfield)
        getRewriter().RemoveText(DeclLoc, Lexer::getLocForEndOfToken(EndLoc, 0, getRewriter().getSourceMgr(), getASTContext().getLangOpts()).getRawEncoding() - DeclLoc.getRawEncoding());
        getRewriter().InsertText(DeclLoc, NewBitfield, true, true);

        return true;
    }

    bool VisitFieldDecl(FieldDecl *Decl) {
        // Check if the field is a bitfield and of enumeration type
        if (Decl->isBitField() && Decl->getType()->isEnumeralType()) {
            TargetBitfields.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<FieldDecl *> TargetBitfields;
    std::string getText(SourceRange Range) {
        return Lexer::getSourceText(
            CharSourceRange::getTokenRange(Range),
            getASTContext().getSourceManager(),
            getASTContext().getLangOpts()).str();
    }
};

// Register the mutator
static RegisterMutator<ChangeBitfieldSize> M(
    "ChangeBitfieldSize",
    "Changes the size of an enumerated bitfield from 3 to 2.");