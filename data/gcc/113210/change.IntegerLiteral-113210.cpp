#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeIntegerLiteralMutator : public Mutator,
    public RecursiveASTVisitor<ChangeIntegerLiteralMutator> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (Literals.empty()) return false;

        IntegerLiteral *Target = randElement(Literals);
        
        SourceRange SR = Target->getSourceRange();
        SourceLocation BeginLoc = SR.getBegin();
        SourceLocation EndLoc = SR.getEnd();
        
        if (BeginLoc.isValid() && EndLoc.isValid()) {
            CharSourceRange Range = CharSourceRange::getTokenRange(BeginLoc, EndLoc);
            getRewriter().ReplaceText(Range, "256");
            return true;
        }
        
        return false;
    }

    bool VisitIntegerLiteral(IntegerLiteral *IL) {
        if (IL->getValue() == 255) {
            Literals.push_back(IL);
        }
        return true;
    }

private:
    std::vector<IntegerLiteral *> Literals;
};

static RegisterMutator<ChangeIntegerLiteralMutator> M(
    "change.IntegerLiteral",
    "Changes integer literal 255 to 256 in the code.");