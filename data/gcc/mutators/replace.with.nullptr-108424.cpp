#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ReplaceWithNullptr : public Mutator,
                          public RecursiveASTVisitor<ReplaceWithNullptr> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        bool Modified = false;

        if (Targets.empty()) return false;
        const auto &Target = randElement(Targets);        

        // for (const auto &Target : Targets) {
            SourceLocation BeginLoc = Target.getBegin();
            SourceLocation EndLoc = Target.getEnd();
            
            if (BeginLoc.isValid() && EndLoc.isValid()) {
                std::string Text = Lexer::getSourceText(
                    CharSourceRange::getTokenRange(BeginLoc, EndLoc),
                    getRewriter().getSourceMgr(),
                    getASTContext().getLangOpts()).str();
                if (Text != "nullptr") {
                    getRewriter().ReplaceText(SourceRange(BeginLoc, EndLoc), "nullptr");
                    Modified = true;
                }
            }
        // }
        return Modified;
    }

    bool VisitIntegerLiteral(IntegerLiteral *IL) {
        Targets.push_back(IL->getSourceRange());
        return true;
    }

    bool VisitFieldDecl(FieldDecl *FD) {
        if (FD->isBitField() && FD->getBitWidth() && !FD->getDeclName()) {
            Targets.push_back(FD->getBitWidth()->getSourceRange());
        }
        return true;
    }

    bool VisitEnumConstantDecl(EnumConstantDecl *ECD) {
        if (ECD->getInitExpr()) {
            Targets.push_back(ECD->getInitExpr()->getSourceRange());
        }
        return true;
    }

    bool VisitAlignedAttr(AlignedAttr *AA) {
        if (AA->getAlignmentExpr()) {
            Targets.push_back(AA->getAlignmentExpr()->getSourceRange());
        }
        return true;
    }

    bool VisitCaseStmt(CaseStmt *CS) {
        if (CS->getLHS()) {
            Targets.push_back(CS->getLHS()->getSourceRange());
        }
        if (CS->getRHS()) {
            Targets.push_back(CS->getRHS()->getSourceRange());
        }
        return true;
    }

    bool VisitStaticAssertDecl(StaticAssertDecl *SAD) {
        Targets.push_back(SAD->getAssertExpr()->getSourceRange());
        return true;
    }

    bool VisitArraySubscriptExpr(ArraySubscriptExpr *ASE) {
        Targets.push_back(ASE->getIdx()->getSourceRange());
        return true;
    }

private:
    std::vector<SourceRange> Targets;
};

static RegisterMutator<ReplaceWithNullptr> M(
    "replace.with.nullptr",
    "Replaces integer literals with nullptr.");