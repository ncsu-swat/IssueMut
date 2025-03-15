#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ReplaceTypeDefinitions : public Mutator, public clang::RecursiveASTVisitor<ReplaceTypeDefinitions> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        SourceManager &SM = getRewriter().getSourceMgr();
        FileID MainFileID = SM.getMainFileID();

        // Get the memory buffer for the main file
        llvm::Optional<llvm::MemoryBufferRef> BufferOrNone = SM.getBufferOrNone(MainFileID);
        if (!BufferOrNone)
            return false;

        llvm::MemoryBufferRef BufferRef = *BufferOrNone;
        StringRef Code = BufferRef.getBuffer();

        // Patterns to search for
        std::string OldTypeDef = "#define TYPE uint32_t";
        std::string NewTypeDef = "#define TYPE uint64_t";
        std::string OldITypeDef = "#define ITYPE int32_t";
        std::string NewITypeDef = "#define ITYPE int64_t";

        size_t PosType = Code.find(OldTypeDef);
        size_t PosIType = Code.find(OldITypeDef);

        bool Modified = false;

        if (PosType != StringRef::npos) {
            SourceLocation StartLoc = SM.getLocForStartOfFile(MainFileID).getLocWithOffset(PosType);
            SourceLocation EndLoc = StartLoc.getLocWithOffset(OldTypeDef.length());
            SourceRange ReplaceRange(StartLoc, EndLoc);

            getRewriter().ReplaceText(ReplaceRange, NewTypeDef);
            Modified = true;
        }

        if (PosIType != StringRef::npos) {
            SourceLocation StartLoc = SM.getLocForStartOfFile(MainFileID).getLocWithOffset(PosIType);
            SourceLocation EndLoc = StartLoc.getLocWithOffset(OldITypeDef.length());
            SourceRange ReplaceRange(StartLoc, EndLoc);

            getRewriter().ReplaceText(ReplaceRange, NewITypeDef);
            Modified = true;
        }

        return Modified;
    }
};

// Register the mutator
static RegisterMutator<ReplaceTypeDefinitions> M(
    "ReplaceTypeDefinitions",
    "Replaces TYPE and ITYPE macro definitions to uint64_t and int64_t respectively.");