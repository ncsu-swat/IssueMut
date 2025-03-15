#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class InlineDeclMutator : public Mutator, public RecursiveASTVisitor<InlineDeclMutator> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (VarDeclsToInline.empty())
            return false;

        // for (auto *VD : VarDeclsToInline) {

        auto *VD = randElement(VarDeclsToInline);

            // if (VD->getNameAsString() == "limit") {
                // Get the initializer expression
                Expr* Init = VD->getInit();
                // if (!Init) continue;
                if (!Init) return false;

                // Get source range for the entire declaration
                SourceRange DeclRange = VD->getSourceRange();
                SourceLocation EndLoc = Lexer::getLocForEndOfToken(
                    DeclRange.getEnd(), 0, getRewriter().getSourceMgr(),
                    getASTContext().getLangOpts());

                // Get empty line range after declaration
                SourceManager &SM = getRewriter().getSourceMgr();
                FileID FID = SM.getFileID(VD->getLocation());
                unsigned LineNum = SM.getSpellingLineNumber(EndLoc);
                SourceLocation NextLineStart = SM.translateLineCol(FID, LineNum+1, 1);

                // Remove declaration and empty line
                getRewriter().RemoveText(SourceRange(DeclRange.getBegin(), NextLineStart));

                // Replace references
                bool modified = false;
                for (const auto& Location : DeclRefLocations) {
                    if (const DeclRefExpr* DRE = dyn_cast<DeclRefExpr>(Location.first)) {
                        if (DRE->getDecl() == VD) {
                            std::string InitText = getSourceText(Init->getSourceRange());
                            getRewriter().ReplaceText(Location.second, InitText);
                            modified = true;
                        }
                    }
                }

                // Remove pragma
                SourceLocation PragmaLoc = SM.translateLineCol(FID, LineNum+1, 1);
                StringRef PragmaLine = Lexer::getSourceText(
                    CharSourceRange::getCharRange(
                        PragmaLoc,
                        SM.translateLineCol(FID, LineNum+2, 1)
                    ),
                    SM,
                    getASTContext().getLangOpts()
                );

                if (PragmaLine.contains("pragma")) {
                    getRewriter().RemoveText(
                        SourceRange(PragmaLoc, SM.translateLineCol(FID, LineNum+2, 1))
                    );
                    modified = true;
                }
            // }
        // }
        return modified;
    }

    bool VisitDeclRefExpr(DeclRefExpr *DRE) {
        DeclRefLocations.push_back(std::make_pair(DRE, DRE->getSourceRange()));
        return true;
    }

    bool VisitVarDecl(VarDecl *VD) {
        if (!VD->isImplicit()) {
            VarDeclsToInline.push_back(VD);
        }
        return true;
    }

private:
    std::vector<VarDecl*> VarDeclsToInline;
    std::vector<std::pair<const DeclRefExpr*, SourceRange>> DeclRefLocations;

    std::string getSourceText(SourceRange Range) {
        return std::string(Lexer::getSourceText(
            CharSourceRange::getTokenRange(Range),
            getRewriter().getSourceMgr(),
            getASTContext().getLangOpts()));
    }
};

static RegisterMutator<InlineDeclMutator> M(
    "inline.decl", 
    "Inlines variable declarations by replacing references with their initializer expression.");