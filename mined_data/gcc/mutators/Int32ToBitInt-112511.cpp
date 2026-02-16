#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class Int32ToBitInt : public Mutator, public RecursiveASTVisitor<Int32ToBitInt> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (Int32Fields.empty()) return false;

        FieldDecl *Field = randElement(Int32Fields);
        SourceRange TypeRange = Field->getTypeSourceInfo()->getTypeLoc().getSourceRange();
        
        getRewriter().ReplaceText(TypeRange, "_BitInt(22)");

        // Remove header
        if (HeaderLoc.isValid() && Int32Fields.size() == 1) {
            getRewriter().RemoveText(
                SourceRange(HeaderLoc, HeaderLoc.getLocWithOffset(20)));
        }

        return true;
    }

    bool VisitFieldDecl(FieldDecl *Field) {
        QualType Type = Field->getType();
        const BuiltinType *BT = Type->getAs<BuiltinType>();
        if (BT && BT->getKind() == BuiltinType::Int) {
            // Check if it's int32_t
            if (Type.getAsString() == "int32_t") {
                Int32Fields.push_back(Field);
                
                // Find and record header location 
                SourceManager &SM = getASTContext().getSourceManager();
                SourceLocation Loc = Field->getBeginLoc();
                if (Loc.isValid()) {
                    StringRef File = SM.getBufferData(SM.getFileID(Loc));
                    size_t Pos = File.find("#include <stdint.h>");
                    if (Pos != StringRef::npos) {
                        HeaderLoc = SM.getLocForStartOfFile(SM.getFileID(Loc))
                                     .getLocWithOffset(Pos);
                    }
                }
            }
        }
        return true;
    }

private:
    std::vector<FieldDecl *> Int32Fields;
    SourceLocation HeaderLoc;
};

static RegisterMutator<Int32ToBitInt> M(
    "Int32ToBitInt", 
    "Replaces int32_t fields with _BitInt(22) in struct definitions.");