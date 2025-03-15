#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class NoreturnToKeyword : public Mutator, public RecursiveASTVisitor<NoreturnToKeyword> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        SM = &getRewriter().getSourceMgr();

        auto MainFileID = SM->getMainFileID();
        llvm::StringRef FileData = SM->getBufferData(MainFileID);

        findAttributeLocations(FileData, "__attribute__((noreturn))");

        if (TargetRanges.empty()) return false;

        SourceRange TargetRange = randElement(TargetRanges);

        getRewriter().ReplaceText(TargetRange, "_Noreturn");

        return true;
    }

private:

    SourceManager *SM = nullptr;

    std::vector<SourceRange> TargetRanges;

    void findAttributeLocations(llvm::StringRef FileData, const std::string &TargetAttribute) {
        size_t Pos = 0;

        while ((Pos = FileData.find(TargetAttribute, Pos)) != llvm::StringRef::npos) {
            // Convert start and end offsets to SourceLocation
            SourceLocation StartLoc = SM->getComposedLoc(SM->getMainFileID(), Pos);
            SourceLocation EndLoc = SM->getComposedLoc(SM->getMainFileID(), Pos + TargetAttribute.length());

            // Create a SourceRange
            SourceRange AttrRange(StartLoc, EndLoc);

            TargetRanges.push_back(AttrRange);

            // Move to the next position
            Pos += TargetAttribute.length();
        }
    }
};

static RegisterMutator<NoreturnToKeyword> M(
    "attribute.NoreturnToKeyword",
    "Replaces __attribute__((noreturn)) with _Noreturn keyword.");