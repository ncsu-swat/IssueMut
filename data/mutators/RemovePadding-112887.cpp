#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemovePadding : public Mutator, public RecursiveASTVisitor<RemovePadding> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetStructs.empty()) return false;

        RecordDecl *StructDecl = randElement(TargetStructs); //TargetStructs[0];
        
        // Find the fields we want to modify
        FieldDecl *FirstField = nullptr;
        FieldDecl *PadField = nullptr;
        FieldDecl *LastField = nullptr;

        for (FieldDecl *Field : StructDecl->fields()) {
            if (!FirstField) {
                FirstField = Field;
            } else if (Field->getType()->isArrayType()) {
                PadField = Field;
            } else {
                LastField = Field;
            }
        }

        if (!FirstField || !PadField || !LastField)
            return false;

        // Get the source manager and language options
        const SourceManager &SM = getRewriter().getSourceMgr();
        const LangOptions &LangOpts = getASTContext().getLangOpts();

        // Get the locations
        // SourceLocation FirstFieldTypeStart = FirstField->getBeginLoc();
        // SourceLocation LastFieldEnd = LastField->getEndLoc();

        SourceLocation PadFieldStart = PadField->getBeginLoc();
        SourceLocation PadFieldEnd = PadField->getEndLoc();

        // Get the text of the first field's type
        // std::string TypeText = "long ";

        // Remove the original field declarations
        // getRewriter().RemoveText(
        //     SourceRange(FirstFieldTypeStart, LastFieldEnd));
        SourceLocation EndLoc = Lexer::getLocForEndOfToken(PadFieldEnd,
            0, getRewriter().getSourceMgr(), getASTContext().getLangOpts());
        getRewriter().RemoveText(
            SourceRange(PadFieldStart, EndLoc));

        // Create the new field declaration
        // std::string NewFields = TypeText + "a, b";
        
        // Insert the new declaration
        // getRewriter().InsertText(FirstFieldTypeStart, NewFields);

        return true;
    }

    bool VisitRecordDecl(RecordDecl *Decl) {
        if (Decl->isStruct() && !Decl->isImplicit()) {
            unsigned FieldCount = 0;
            bool HasPadding = false;
            
            for (FieldDecl *Field : Decl->fields()) {
                FieldCount++;
                if (Field->getType()->isArrayType()) {
                    HasPadding = true;
                }
            }
            
            if (FieldCount >= 3 && HasPadding) {
                TargetStructs.push_back(Decl);
            }
        }
        return true;
    }

private:
    std::vector<RecordDecl *> TargetStructs;
};

static RegisterMutator<RemovePadding> M(
    "RemovePadding",
    "Removes padding field from struct and combines field declarations.");