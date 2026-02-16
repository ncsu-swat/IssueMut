#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeAsmConstraint : public Mutator, public RecursiveASTVisitor<ChangeAsmConstraint> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        AsmDeclMutated = false;
        TraverseAST(getASTContext());

        if (TargetAsmConstraints.empty()) {
            return AsmDeclMutated;
        }

        // Select a random union declaration to modify
        GCCAsmStmt *AsmStmt = randElement(TargetAsmConstraints);
        
        unsigned NumOutputs = AsmStmt->getNumOutputs();
        for (unsigned i = 0; i < NumOutputs; ++i) {
            StringRef ConstraintStrRef = AsmStmt->getOutputConstraint(i);
            std::string ConstraintStr = ConstraintStrRef.str();
            if (ConstraintStr != "+r")
                continue;
            Expr *E = AsmStmt->getOutputExpr(i);
            // Perform mutation

            // Get the constraint StringLiteral
            StringLiteral *ConstraintLiteral = AsmStmt->getOutputConstraintLiteral(i);

            // Get the SourceRange of the constraint
            SourceRange ConstraintRange = ConstraintLiteral->getSourceRange();

            // Use Lexer to get the exact range in the source code
            SourceManager &SM = getRewriter().getSourceMgr();
            LangOptions LangOpts = getASTContext().getLangOpts();
            // Adjust the range to include any macros or escaped characters
            CharSourceRange CharRange = Lexer::makeFileCharRange(
                CharSourceRange::getTokenRange(ConstraintRange),
                SM, LangOpts);
            if (CharRange.isInvalid())
                return false;

            // Replace the constraint with "+d"
            getRewriter().ReplaceText(CharRange, "\"+d\"");
        }
        return true;
    }

    bool VisitVarDecl(VarDecl *VD) {
        // Get the SourceRange of the VarDecl
        SourceRange DeclRange = VD->getSourceRange();

        SourceManager &SM = getRewriter().getSourceMgr();
        LangOptions LangOpts = getASTContext().getLangOpts();

        CharSourceRange CharRange = Lexer::makeFileCharRange(
            CharSourceRange::getTokenRange(DeclRange), SM, LangOpts);
        if (CharRange.isInvalid())
            return true;

        StringRef DeclText = Lexer::getSourceText(CharRange, SM, LangOpts);
        std::string DeclStr = DeclText.str();

        // Replace '__asm__' with '__asm' in DeclStr
        size_t Pos = DeclStr.find("__asm__");
        if (Pos != std::string::npos) {
            DeclStr.replace(Pos, 7, "__asm");
            getRewriter().ReplaceText(CharRange, DeclStr);
            AsmDeclMutated = true;
        }
        return true;
    }

    bool VisitGCCAsmStmt(GCCAsmStmt *S) {
        unsigned NumOutputs = S->getNumOutputs();
        for (unsigned i = 0; i < NumOutputs; ++i) {
            StringRef ConstraintStrRef = S->getOutputConstraint(i);
            std::string ConstraintStr = ConstraintStrRef.str();
            if (ConstraintStr != "+r")
                continue;
            TargetAsmConstraints.push_back(S);
        }

        return true;
    }

private:
    bool AsmDeclMutated;
    std::vector<GCCAsmStmt *> TargetAsmConstraints;
};

// Register the mutator
static RegisterMutator<ChangeAsmConstraint> M(
    "ChangeAsmConstraint",
    "Changes the asm constraint '+r' to '+d' for variable 'a' in GCC inline assembly and replaces '__asm__' with '__asm' in the declarations of 'a' and 'b'."
);