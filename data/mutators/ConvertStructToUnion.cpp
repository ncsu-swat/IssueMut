#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/Type.h>        // For ElaboratedType
#include <clang/AST/TypeLoc.h>     // For TypeLoc and ElaboratedTypeLoc
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ConvertStructToUnion : public Mutator, public RecursiveASTVisitor<ConvertStructToUnion> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        // First, traverse to collect structs
        TraverseDecl(getASTContext().getTranslationUnitDecl());
        if (TargetStructs.empty()) return false;

        // Randomly select a struct to convert
        StructDecl = randElement(TargetStructs);

        // Store the canonical QualType of the struct
        StructType = getASTContext().getRecordType(StructDecl).getCanonicalType().getUnqualifiedType();

        // Convert the struct declaration to a union
        if (!convertStructToUnion(StructDecl)) return false;

        // Now, traverse the AST again to update references
        Rewriting = true;
        TraverseDecl(getASTContext().getTranslationUnitDecl());

        return true;
    }

    bool VisitRecordDecl(RecordDecl *Decl) {
        if (!Rewriting) {
            if (Decl->isStruct() && !Decl->isImplicit()) {
                TargetStructs.push_back(Decl);
            }
        }
        return true;
    }

    bool VisitTypeLoc(TypeLoc TL) {
        if (!Rewriting) return true;

        QualType QT = TL.getType();
        if (QT.getCanonicalType().getUnqualifiedType() == StructType.getCanonicalType().getUnqualifiedType()) {
            if (ElaboratedTypeLoc ETL = TL.getAs<ElaboratedTypeLoc>()) {
                // Get the underlying ElaboratedType
                const ElaboratedType *ET = ETL.getTypePtr();
                // Get the keyword
                ElaboratedTypeKeyword Keyword = ET->getKeyword();
                // Get the keyword location
                SourceLocation KeywordLoc = ETL.getElaboratedKeywordLoc();
                if (KeywordLoc.isValid()) {
                    if (Keyword == ETK_Struct) {
                        // Replace 'struct' with 'union'
                        getRewriter().ReplaceText(KeywordLoc, 6, "union ");
                    }
                }
            }
        }
        return true;
    }

private:
    std::vector<RecordDecl *> TargetStructs;
    RecordDecl *StructDecl = nullptr;
    QualType StructType;
    bool Rewriting = false;

    // Converts the struct declaration to a union
    bool convertStructToUnion(RecordDecl *StructDecl) {
        SourceLocation KeywordLoc = StructDecl->getInnerLocStart();
        if (KeywordLoc.isInvalid()) return false;

        // Replace 'struct' with 'union'
        getRewriter().ReplaceText(KeywordLoc, 6, "union ");
        return true;
    }
};

// Register the mutator
static RegisterMutator<ConvertStructToUnion> M(
    "ConvertStructToUnion",
    "Converts a struct to a union and updates associated variables and parameters.");