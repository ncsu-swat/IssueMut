#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class MagicNumberToSizeofMutator : public Mutator, 
    public RecursiveASTVisitor<MagicNumberToSizeofMutator> {

public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        return modified;
    }

    bool VisitIntegerLiteral(IntegerLiteral *IL) {
        // Only modify if value is 64
        if (IL->getValue() != 64)
            return true;

        SourceLocation Loc = IL->getLocation();
        if (!Loc.isValid())
            return true;

        // Get the source text for the integer literal
        SourceManager &SM = getRewriter().getSourceMgr();
        CharSourceRange Range = CharSourceRange::getTokenRange(Loc, Loc);
        StringRef Text = Lexer::getSourceText(Range, SM, getASTContext().getLangOpts());

        TypedefDecl* TypedefDecl = randElement(TypedefDecls);

        if (Text == "64") {
            std::string text = "(sizeof(" + TypedefDecl->getNameAsString() + ") * 8)";
            getRewriter().ReplaceText(Loc, Text.size(), text);
            // getRewriter().ReplaceText(Loc, Text.size(), "(sizeof(eword_t) * 8)");
            modified = true;
        }

        return true;
    }

    bool VisitTypedefDecl(TypedefDecl *TD) {
        SourceManager &SM = getASTContext().getSourceManager();
        SourceLocation Loc = TD->getLocation();

        // Check if the typedef is in the main file
        if (SM.isInMainFile(Loc)) {
            TypedefDecls.push_back(TD);
        }

        return true;
    }

private:
    bool modified = false;
    std::vector<TypedefDecl*> TypedefDecls;
};

static RegisterMutator<MagicNumberToSizeofMutator> M(
    "replace.MagicNumber", 
    "Replaces magic number 64 with sizeof(eword_t) * 8");