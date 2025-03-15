#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ReplaceReturnWithUnreachable : public Mutator, 
    public RecursiveASTVisitor<ReplaceReturnWithUnreachable> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (ReturnStmts.empty()) return false;

        // Find last return statement in function
        ReturnStmt *Target = nullptr;
        for (auto RS : ReturnStmts) {
            if (!Target || getSourceManager().isBeforeInTranslationUnit(
                Target->getBeginLoc(), RS->getBeginLoc())) {
                Target = RS;
            }
        }
        
        if (!Target) return false;

        SourceRange Range = Target->getSourceRange();
        getRewriter().ReplaceText(Range, "__builtin_unreachable ()");

        return true;
    }

    bool VisitReturnStmt(ReturnStmt *RS) {
        ReturnStmts.push_back(RS);
        return true;
    }

private:
    std::vector<ReturnStmt*> ReturnStmts;
};

static RegisterMutator<ReplaceReturnWithUnreachable> M(
    "replace.return.unreachable", 
    "Replaces the last return statement with __builtin_unreachable().");