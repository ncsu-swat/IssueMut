#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveMemcmpMutator : public Mutator, 
    public RecursiveASTVisitor<RemoveMemcmpMutator> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (MemcmpFuncs.empty()) return false;

        // Get the function to remove
        FunctionDecl *FuncToRemove = randElement(MemcmpFuncs);

        // Get source range for the entire function
        SourceRange RemoveRange = FuncToRemove->getSourceRange();
        
        // Get the rewriter to remove the function
        getRewriter().RemoveText(RemoveRange);

        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *Decl) {
        // if (Decl->getNameAsString() == "compare") {
            MemcmpFuncs.push_back(Decl);
        // }
        return true;
    }

private:
    std::vector<FunctionDecl *> MemcmpFuncs;
};

static RegisterMutator<RemoveMemcmpMutator> M(
    "remove.memcmp", 
    "Removes functions containing memcmp calls");