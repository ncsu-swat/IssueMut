#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveClassField : public Mutator, public RecursiveASTVisitor<RemoveClassField> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetFields.empty()) return false;

        FieldDecl *Field = randElement(TargetFields);
        
        // Get the field's source range
        SourceRange RemoveRange = Field->getSourceRange();
        
        // Get the location after the semicolon
        SourceLocation EndLoc = Lexer::findLocationAfterToken(RemoveRange.getEnd(), 
            tok::semi, getRewriter().getSourceMgr(),
            getASTContext().getLangOpts(), false);
            
        if (EndLoc.isInvalid())
            return false;

        // Remove the field including trailing semicolon and newline
        getRewriter().RemoveText(SourceRange(RemoveRange.getBegin(), EndLoc));

        return true;
    }

    bool VisitFieldDecl(FieldDecl *Field) {
        // if (Field->getNameAsString() == "dummy") {
            TargetFields.push_back(Field);
        // }
        return true;
    }

private:
    std::vector<FieldDecl *> TargetFields;
};

static RegisterMutator<RemoveClassField> M(
    "remove.ClassField", 
    "Removes the 'dummy' field from the LoadGraph class");