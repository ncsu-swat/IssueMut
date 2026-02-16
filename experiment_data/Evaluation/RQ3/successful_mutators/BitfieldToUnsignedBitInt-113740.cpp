#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class BitfieldToUnsignedBitInt : public Mutator,
    public RecursiveASTVisitor<BitfieldToUnsignedBitInt> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetBitfields.empty()) return false;

        FieldDecl *BitfieldDecl = randElement(TargetBitfields);

        SourceLocation StartLoc = BitfieldDecl->getBeginLoc();
        SourceLocation ColonLoc = BitfieldDecl->getBitWidth()->getBeginLoc();

        if (StartLoc.isInvalid() || ColonLoc.isInvalid())
            return false;

        getRewriter().ReplaceText(
            SourceRange(StartLoc, ColonLoc.getLocWithOffset(-1)),
            "unsigned _BitInt(32) : ");

        return true;
    }

    bool VisitFieldDecl(FieldDecl *Decl) {
        if (Decl->isBitField() && !Decl->isImplicit()) {
            TargetBitfields.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<FieldDecl *> TargetBitfields;
};

static RegisterMutator<BitfieldToUnsignedBitInt> M(
    "BitfieldToUnsignedBitInt",
    "Replace int bitfield with unsigned _BitInt(32) bitfield.");