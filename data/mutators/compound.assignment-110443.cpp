#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class CompoundAssignmentMutator : public Mutator,
    public RecursiveASTVisitor<CompoundAssignmentMutator> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (MutationTargets.empty()) return false;

        // Select a random target to modify
        auto Target = randElement(MutationTargets);
        
        DeclStmt *Decl = Target.first;
        BinaryOperator *FirstAssign = Target.second.first;
        BinaryOperator *SecondAssign = Target.second.second;

        // // Get the right-hand side expression (array access)
        // std::string RHSText = getText(FirstAssign->getRHS()->getSourceRange());
        
        std::string realText = getText(FirstAssign->getLHS()->getSourceRange());
        std::string imagText = getText(SecondAssign->getLHS()->getSourceRange());
        
        VarDecl *VariableDecl = nullptr;
        for (auto *D: Decl->decls()){
            if (auto *VD = dyn_cast<VarDecl>(D)) {
                VariableDecl = VD;
            }
        }

        if (VariableDecl == nullptr) {
            return false;
        }

        const Expr *InitExpr = VariableDecl->getInit();

        std::string InitStr = getText(InitExpr->getSourceRange());

        // Create the compound assignment
        
        // std::string NewAssign = "buf1[a52_imdct_256_i].real = buf1[a52_imdct_256_i].imag = "
        //                        "a52_imdct_256_data[a52_imdct_256_k]";
        
        std::string NewAssign = realText + " = " + imagText + " = " + InitStr;

        // Remove original statements and insert new one
        SourceRange RemoveRange(
            Decl->getBeginLoc(),
            SecondAssign->getEndLoc());
        
        getRewriter().ReplaceText(RemoveRange, NewAssign);

        return true;
    }

    bool VisitForStmt(ForStmt *FS) {
        if (auto Body = dyn_cast<CompoundStmt>(FS->getBody())) {
            for (auto I = Body->body_begin(); I != Body->body_end(); ++I) {
                if (auto Decl = dyn_cast<DeclStmt>(*I)) {
                    auto Next = std::next(I);
                    if (Next != Body->body_end()) {
                        if (auto FirstAssign = dyn_cast<BinaryOperator>(*Next)) {
                            auto NextNext = std::next(Next);
                            if (NextNext != Body->body_end()) {
                                if (auto SecondAssign = dyn_cast<BinaryOperator>(*NextNext)) {
                                    if (FirstAssign->isAssignmentOp() && 
                                        SecondAssign->isAssignmentOp()) {
                                        MutationTargets.push_back({Decl,
                                            {FirstAssign, SecondAssign}});
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

private:
    std::vector<std::pair<DeclStmt*, 
        std::pair<BinaryOperator*, BinaryOperator*>>> MutationTargets;

    std::string getText(SourceRange Range) {
        return Lexer::getSourceText(
            CharSourceRange::getTokenRange(Range),
            getASTContext().getSourceManager(),
            getASTContext().getLangOpts()).str();
    }
};

static RegisterMutator<CompoundAssignmentMutator> M(
    "compound.assignment",
    "Combines consecutive assignments into compound assignment.");