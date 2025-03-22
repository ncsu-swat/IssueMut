#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveTypedef : public Mutator, public clang::RecursiveASTVisitor<RemoveTypedef> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetTypedefs.empty()) return false;

        // Select the specific typedef for removal
        TypedefDecl *TypedefDecl = randElement(TargetTypedefs); // TargetTypedefs.front();

        // Get the source range for the typedef declaration
        SourceRange SR = TypedefDecl->getSourceRange();
        
        // Calculate the start and end locations
        SourceLocation StartLoc = SR.getBegin();
        SourceLocation EndLoc = SR.getEnd();

        // Remove the typedef declaration from the source code
        getRewriter().RemoveText(SourceRange(StartLoc,
                                             Lexer::getLocForEndOfToken(EndLoc, 0, getRewriter().getSourceMgr(), getASTContext().getLangOpts())));     

        return true;
    }

    bool VisitTypedefDecl(TypedefDecl *Decl) {
        // Check if the declaration is for int64x1x4_t
        // if (Decl->getName() == "int64x1x4_t") {
            TargetTypedefs.push_back(Decl);
        // }
        return true;
    }

private:
    std::vector<TypedefDecl *> TargetTypedefs;
};

// Register the mutator
static RegisterMutator<RemoveTypedef> M(
    "RemoveTypedef",
    "Removes the typedef declaration for 'int64x1x4_t'.");