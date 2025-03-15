#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class AddUnionField : public Mutator, public clang::RecursiveASTVisitor<AddUnionField> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetUnions.empty()) return false;

        // Select a random union declaration to modify
        RecordDecl *UnionDecl = randElement(TargetUnions);
        
        // Get the location of the closing brace
        SourceLocation EndLoc = UnionDecl->getSourceRange().getEnd();
        SourceLocation InsertLoc = Lexer::getLocForEndOfToken(
            EndLoc, 1, getRewriter().getSourceMgr(), getASTContext().getLangOpts());
        if (InsertLoc.isInvalid())
            return false;

        std::string NewField = "    long double __mutated_field__;\n";
        getRewriter().InsertTextBefore(InsertLoc, NewField);

        return true;
    }

    bool VisitRecordDecl(RecordDecl *Decl) {
        // Check if the declaration is a union
        if (Decl->isUnion() && !Decl->isImplicit()) {
            TargetUnions.push_back(Decl);
        }
        return true;
    }

private:
    std::vector<RecordDecl *> TargetUnions;
};

// Register the mutator
static RegisterMutator<AddUnionField> M(
    "AddUnionField",
    "Adds a field of type 'long double' to a randomly selected union.");