#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class InlineAsmSimplifier : public Mutator, public RecursiveASTVisitor<InlineAsmSimplifier> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetStmts.empty()) return false;

        auto *Stmt = randElement(TargetStmts);
        auto Range = Stmt->getAsmString()->getSourceRange();
        
        std::string NewAsm = "\"@ naked\"";
        getRewriter().ReplaceText(Range, NewAsm);

        return true;
    }

    bool VisitGCCAsmStmt(GCCAsmStmt *Stmt) {
        if (!Stmt->isVolatile()) return true;
        
        // Only target specific asm statement
        // std::string AsmString = Stmt->getAsmString()->getString().str();
        // if (AsmString.find("@ naked") != std::string::npos && 
        //     AsmString.find("ret") != std::string::npos) {
            TargetStmts.push_back(Stmt);
        // }
        return true;
    }

private:
    std::vector<GCCAsmStmt *> TargetStmts;
};

static RegisterMutator<InlineAsmSimplifier> M(
    "asm.InlineAsmSimplifier", 
    "Simplifies inline assembly statements by removing the ret instruction.");