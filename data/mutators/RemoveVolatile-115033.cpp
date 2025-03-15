#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveVolatile : public Mutator, public RecursiveASTVisitor<RemoveVolatile> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (VolatileFields.empty()) return false;

        FieldDecl *Field = randElement(VolatileFields);
        
        // Get the source range of the volatile qualifier
        SourceRange VolatileRange = Field->getSourceRange();
        QualType Type = Field->getType();
        
        if (const PointerType *PT = Type->getAs<PointerType>()) {
            if (PT->getPointeeType().isVolatileQualified()) {
                // Find location of 'volatile' keyword
                auto &SM = getRewriter().getSourceMgr();
                auto Begin = SM.getSpellingLoc(Field->getBeginLoc());
                
                // Get the text from start to pointer declaration
                std::string TypeStr = Lexer::getSourceText(
                    CharSourceRange::getCharRange(
                        Begin,
                        Field->getTypeSourceInfo()->getTypeLoc().getBeginLoc()
                    ),
                    SM,
                    getASTContext().getLangOpts()
                ).str();
                
                // Remove 'volatile' from the declaration
                size_t pos = TypeStr.find("volatile");
                if (pos != std::string::npos) {
                    SourceLocation VolBegin = Begin.getLocWithOffset(pos);
                    SourceLocation VolEnd = VolBegin.getLocWithOffset(8); // "volatile"
                    getRewriter().RemoveText(SourceRange(VolBegin, VolEnd));
                }
                
                return true;
            }
        }
        return false;
    }

    bool VisitFieldDecl(FieldDecl *Field) {
        QualType Type = Field->getType();
        if (const PointerType *PT = Type->getAs<PointerType>()) {
            if (PT->getPointeeType().isVolatileQualified()) {
                VolatileFields.push_back(Field);
            }
        }
        return true;
    }

private:
    std::vector<FieldDecl *> VolatileFields;
};

static RegisterMutator<RemoveVolatile> M(
    "RemoveVolatile", 
    "Removes volatile qualifier from pointer type fields in structures.");