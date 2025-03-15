#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveCompoundLiteral : public Mutator, 
    public RecursiveASTVisitor<RemoveCompoundLiteral> {

public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        // if (!Target) return false;
        if (Targets.empty()) return false;

        // Get the literal value from the initializer
        CompoundLiteralExpr *Target = randElement(Targets);
        auto *InitList = cast<InitListExpr>(Target->getInitializer());
        if (!InitList || InitList->getNumInits() == 0) return false;
        
        Expr *LiteralExpr = InitList->getInit(0);
        
        // Get source range for literal expression
        SourceRange Range = LiteralExpr->getSourceRange();
        SourceManager &SM = getRewriter().getSourceMgr();
        
        // Get text of literal expression
        CharSourceRange CharRange = CharSourceRange::getTokenRange(Range);
        std::string ReplacementText = Lexer::getSourceText(CharRange, SM, 
                                        getASTContext().getLangOpts()).str();

        // Replace compound literal with just the literal value
        getRewriter().ReplaceText(Target->getSourceRange(), ReplacementText);

        return true;
    }

    bool VisitCompoundLiteralExpr(CompoundLiteralExpr *E) {
        // Target = E;
        Targets.push_back(E);
        return true;
    }

private:
    // CompoundLiteralExpr *Target = nullptr;
    std::vector<CompoundLiteralExpr *> Targets;
};

static RegisterMutator<RemoveCompoundLiteral> M(
    "remove.compound.literal", 
    "Removes compound literal syntax and keeps only the literal value.");