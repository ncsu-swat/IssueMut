#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h> 
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveTypeCasts : public Mutator, public RecursiveASTVisitor<RemoveTypeCasts> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (Targets.empty()) return false;

        auto Target = randElement(Targets);
        getRewriter().ReplaceText(Target.first, Target.second);

        return true;
    }

    bool VisitCStyleCastExpr(CStyleCastExpr *Cast) {
        // Skip if in a macro expansion
        if (Cast->getExprLoc().isMacroID())
            return true;

        // Skip if casting to void
        if (Cast->getType()->isVoidType()) 
            return true;

        // Get the inner expression
        Expr *InnerExpr = Cast->getSubExpr()->IgnoreParenImpCasts();
        
        // Get source text
        SourceRange CastRange = Cast->getSourceRange();
        
        // If the inner expression contains 'LL' suffix, preserve it
        SourceRange InnerRange = InnerExpr->getSourceRange();
        std::string InnerText = getSourceText(InnerRange);
        
        // Remove 'LL' suffix from integer literals
        size_t pos = InnerText.find("LL");
        if (pos != std::string::npos) {
            InnerText = InnerText.substr(0, pos);
        }
        Targets.push_back({CastRange, InnerText});
        
        // getRewriter().ReplaceText(CastRange, InnerText);
        
        return true;
    }

private:
    std::string getSourceText(SourceRange Range) {
        return std::string(Lexer::getSourceText(
            CharSourceRange::getTokenRange(Range),
            getRewriter().getSourceMgr(),
            getASTContext().getLangOpts()));
    }
    std::vector<std::pair<SourceRange, std::string>> Targets;
};

static RegisterMutator<RemoveTypeCasts> X(
    "remove.typecasts.116544", 
    "Removes C-style type casts.");