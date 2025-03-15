#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class MoveGlobalVarToLocal
    : public Mutator,
      public RecursiveASTVisitor<MoveGlobalVarToLocal> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        // Traverse the AST to collect global variables and their usage
        TraverseDecl(getASTContext().getTranslationUnitDecl());

        // Find global variables used only in one function
        std::vector<std::pair<VarDecl *, FunctionDecl *>> Candidates;
        for (auto &Entry : VarUses) {
            VarDecl *VD = Entry.first;
            const std::set<FunctionDecl *> &Funcs = Entry.second;
            if (Funcs.size() == 1 && GlobalVars.count(VD)) {
                Candidates.emplace_back(VD, *Funcs.begin());
            }
        }

        if (Candidates.empty())
            return false;

        // Select a random candidate
        auto &Candidate = randElement(Candidates);
        VarDecl *VD = Candidate.first;
        FunctionDecl *FD = Candidate.second;

        // Remove the variable declaration from global scope
        SourceRange DeclRange = VD->getSourceRange();
        DeclRange = getExpansionRange(DeclRange);

        // Extend the source range to include the semicolon
        SourceLocation EndLoc = Lexer::getLocForEndOfToken(DeclRange.getEnd(),
            0, getRewriter().getSourceMgr(), getASTContext().getLangOpts());
        if (EndLoc.isValid())
            DeclRange.setEnd(EndLoc);

        getRewriter().RemoveText(DeclRange);

        // Get the source text of the variable declaration
        std::string VarDeclStr = getSourceText(VD);

        // Ensure the declaration ends with a semicolon
        if (!VarDeclStr.empty() && VarDeclStr.back() != ';') {
            VarDeclStr += ";";
        }

        // Insert the variable declaration into the function body
        CompoundStmt *Body = dyn_cast<CompoundStmt>(FD->getBody());
        if (!Body)
            return false;

        // Insert after the opening brace of the function body
        SourceLocation InsertLoc = Body->getLBracLoc().getLocWithOffset(1);
        getRewriter().InsertTextAfter(InsertLoc, "\n" + VarDeclStr + "\n");

        return true;
    }

    bool VisitVarDecl(VarDecl *VD) {
        if (VD->isFileVarDecl() && !VD->isImplicit()) {
            GlobalVars.insert(VD);
        }
        return true;
    }

    bool VisitDeclRefExpr(DeclRefExpr *DRE) {
        if (VarDecl *VD = dyn_cast<VarDecl>(DRE->getDecl())) {
            if (GlobalVars.count(VD)) {
                if (CurrentFunction) {
                    VarUses[VD].insert(CurrentFunction);
                } else {
                    // Used outside of any function
                    UsedInGlobalScope.insert(VD);
                }
            }
        }
        return true;
    }

    // Keep track of the current function context
    bool TraverseFunctionDecl(FunctionDecl *FD) {
        FunctionDecl *PreviousFunction = CurrentFunction;
        CurrentFunction = FD;
        bool Result = RecursiveASTVisitor::TraverseFunctionDecl(FD);
        CurrentFunction = PreviousFunction;
        return Result;
    }

private:
    std::set<VarDecl *> GlobalVars;
    std::map<VarDecl *, std::set<FunctionDecl *>> VarUses;
    std::set<VarDecl *> UsedInGlobalScope;
    FunctionDecl *CurrentFunction = nullptr;
};

static RegisterMutator<MoveGlobalVarToLocal> M(
    "MoveGlobalVarToLocal",
    "Moves a global variable into a function if it is only used within that function.");