#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveVolatileQualifier108790 : public Mutator, 
    public RecursiveASTVisitor<RemoveVolatileQualifier108790> {

public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        // if (TargetExpr == nullptr) return false;
        if (TargetExprs.empty()) return false;

        CStyleCastExpr *TargetExpr = randElement(TargetExprs);

        // Get source text for the entire cast expression
        SourceRange Range = TargetExpr->getSourceRange();
        CharSourceRange CharRange = CharSourceRange::getTokenRange(Range);
        StringRef ExprText = Lexer::getSourceText(CharRange, 
                                                getRewriter().getSourceMgr(),
                                                getASTContext().getLangOpts());

        // Remove 'volatile' from the text
        std::string NewText = ExprText.str();
        size_t pos = NewText.find("volatile");
        if (pos != std::string::npos) {
            NewText.erase(pos, 9); // "volatile "
        }

        getRewriter().ReplaceText(Range, NewText);
        return true;
    }

    bool VisitCStyleCastExpr(CStyleCastExpr *E) {
        QualType Type = E->getType();
        if (Type->isPointerType() && 
            Type->getPointeeType().isVolatileQualified()) {
            // TargetExpr = E;
            TargetExprs.push_back(E);
        }
        return true;
    }

private:
    // CStyleCastExpr *TargetExpr = nullptr;
    std::vector<CStyleCastExpr *> TargetExprs;
};

static RegisterMutator<RemoveVolatileQualifier108790> M(
    "remove.volatile.108790",
    "Removes volatile qualifier from pointer cast expressions.");
