#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class BufferTypeChange : public Mutator, 
    public RecursiveASTVisitor<BufferTypeChange> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        // if (TargetVarDecl == nullptr) return false;
        if (TargetVars.empty()) return false;

        VarDecl *TargetVarDecl = randElement(TargetVars);

        SourceLocation TypeLoc = TargetVarDecl->getTypeSourceInfo()
            ->getTypeLoc().getBeginLoc();
        
        // Get the full length of "unsigned char"
        SourceLocation ArrayDeclEnd = TargetVarDecl->getEndLoc();
        
        // Replace "unsigned char buf[1 << 16]" with 
        // "uint32_t buf[(1 << 16) / sizeof(uint32_t)]"
        std::string NewDecl = "uint32_t " + TargetVarDecl->getNameAsString() + "[(1 << 16) / sizeof(uint32_t)]";
        
        SourceRange ReplaceRange(TypeLoc, ArrayDeclEnd);
        getRewriter().ReplaceText(ReplaceRange, NewDecl);
        
        return true;
    }

    bool VisitVarDecl(VarDecl *Decl) {
        if (/* Decl->getNameAsString() == "buf" && */
            Decl->getType()->isArrayType()) {
            const ArrayType *AT = Decl->getType()->getAsArrayTypeUnsafe();
            if (AT && AT->getElementType()->isCharType()) {
                // TargetVarDecl = Decl;
                TargetVars.push_back(Decl);
            }
        }
        return true;
    }

private:
    // VarDecl *TargetVarDecl = nullptr;
    std::vector<VarDecl *> TargetVars;
};

static RegisterMutator<BufferTypeChange> X(
    "buf.TypeChange", 
    "Changes buffer type from unsigned char to uint32_t with size adjustment");