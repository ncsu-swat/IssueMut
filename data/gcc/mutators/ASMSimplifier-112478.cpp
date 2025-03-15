#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ASMSimplifier : public Mutator, public RecursiveASTVisitor<ASMSimplifier> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (RegisterDecls.empty() && ASMStmts.empty()) return false;

        // for (auto Decl : RegisterDecls) {
        auto Decl = randElement(RegisterDecls);
            SourceRange RemoveRange = Decl->getSourceRange();
            getRewriter().RemoveText(RemoveRange);
        // }

        // for (auto ASM : ASMStmts) {
        auto ASM = randElement(ASMStmts);
            std::string NewASM = "asm volatile(\"# \" : ::\"ra\")";
            SourceRange Range = ASM->getSourceRange();
            getRewriter().ReplaceText(Range, NewASM);
        // }

        return true;
    }

    bool VisitDeclStmt(DeclStmt *Stmt) {
        for (auto D : Stmt->decls()) {
            if (auto VD = dyn_cast<VarDecl>(D)) {
                if (VD->getStorageClass() == SC_Register) {
                    RegisterDecls.push_back(Stmt);
                }
            }
        }
        return true;
    }

    bool VisitGCCAsmStmt(GCCAsmStmt *Stmt) {
        ASMStmts.push_back(Stmt);
        return true;
    }

private:
    std::vector<DeclStmt*> RegisterDecls;
    std::vector<GCCAsmStmt*> ASMStmts;
};

static RegisterMutator<ASMSimplifier> M(
    "ASMSimplifier", 
    "Simplifies assembly statements and removes register declarations.");