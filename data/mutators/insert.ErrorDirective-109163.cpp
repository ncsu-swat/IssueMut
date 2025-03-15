#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class InsertErrorDirective : public Mutator, public RecursiveASTVisitor<InsertErrorDirective> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        
        SourceManager &SM = getASTContext().getSourceManager();
        FileID MainFileID = SM.getMainFileID();
        
        // Get start of file location
        SourceLocation StartLoc = SM.getLocForStartOfFile(MainFileID);
        if (StartLoc.isInvalid())
            return false;

        // Replace entire file content
        // SourceLocation EndLoc = SM.getLocForEndOfFile(MainFileID);
        // if (EndLoc.isInvalid())
        //     return false;

        // SourceRange FileRange(StartLoc, EndLoc);
        getRewriter().InsertTextBefore(StartLoc, "#error message\n");
        return true;
    }
};

static RegisterMutator<InsertErrorDirective> M(
    "insert.ErrorDirective", 
    "Inserts a #error directive at the start of the file.");