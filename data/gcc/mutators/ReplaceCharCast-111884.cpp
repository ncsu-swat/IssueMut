#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ReplaceCharCast : public Mutator, public clang::RecursiveASTVisitor<ReplaceCharCast> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetCasts.empty())
            return false;

        // Select a random cast expression to modify
        CStyleCastExpr *CastExpr = randElement(TargetCasts);

        // Get the TypeLoc corresponding to the cast type
        TypeSourceInfo *TSI = CastExpr->getTypeInfoAsWritten();
        TypeLoc TL = TSI->getTypeLoc();
        SourceRange TypeRange = TL.getSourceRange();

        QualType OldType = CastExpr->getTypeAsWritten();

        if (OldType->isPointerType()) {
            ASTContext &Ctx = getASTContext();

            // Get pointer qualifiers (e.g., const in 'char * const')
            Qualifiers PtrQuals = OldType.getLocalQualifiers();

            QualType PointeeType = OldType->getPointeeType();

            // Get pointee qualifiers (e.g., const in 'const char *')
            Qualifiers PointeeQuals = PointeeType.getLocalQualifiers();

            // Check if PointeeType is 'char'
            if (PointeeType->isCharType()) {
                // Create 'unsigned char' type with pointee qualifiers
                QualType UnsignedCharType = Ctx.UnsignedCharTy; // 'unsigned char'
                UnsignedCharType = Ctx.getQualifiedType(UnsignedCharType, PointeeQuals);

                // Create new pointer type
                QualType NewPtrType = Ctx.getPointerType(UnsignedCharType);
                // Apply pointer qualifiers
                NewPtrType = Ctx.getQualifiedType(NewPtrType, PtrQuals);

                // Get the NewTypeStr
                PrintingPolicy PP = Ctx.getPrintingPolicy();
                std::string NewTypeStr = NewPtrType.getAsString(PP);

                // Replace the type in the cast expression
                getRewriter().ReplaceText(TypeRange, NewTypeStr);

                return true;
            }
        }
        return false;
    }

    bool VisitCStyleCastExpr(CStyleCastExpr *Cast) {
        QualType CastType = Cast->getTypeAsWritten();

        if (CastType->isPointerType()) {
            QualType PointeeType = CastType->getPointeeType();
            if (PointeeType->isCharType()) {
                // It's a cast to 'char *' (with any qualifiers)
                TargetCasts.push_back(Cast);
            }
        }
        return true;
    }

private:
    std::vector<CStyleCastExpr *> TargetCasts;
};

// Register the mutator
static RegisterMutator<ReplaceCharCast> M(
    "ReplaceCharCast",
    "Replaces casts to 'char *' with 'unsigned char *' in a randomly selected instance.");