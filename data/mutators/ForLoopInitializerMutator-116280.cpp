#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ForLoopInitializerMutator : public Mutator, public RecursiveASTVisitor<ForLoopInitializerMutator> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        return !TargetForLoops.empty();
    }

    bool VisitForStmt(ForStmt *ForLoop) {
        // Check if there's an initializer in the for loop
        if (ForLoop->getInit() != nullptr) {
            // We need to handle the initializer, which is expected to be a DeclStmt
            if (auto *InitDecl = dyn_cast<DeclStmt>(ForLoop->getInit())) {
                // Iterate through all declarations in the declaration statement
                for (auto *Decl : InitDecl->decls()) {
                    if (auto *Var = dyn_cast<VarDecl>(Decl)) {
                        // Get the location to insert the new initializer
                        SourceRange InitRange = ForLoop->getInit()->getSourceRange();
                        getRewriter().RemoveText(InitRange); // Remove the old initializer
                        
                        // Insert text for the new initializer without assignment
                        std::string newInitializer = "int " + Var->getName().str() + ";";
                        SourceLocation InsertLoc = InitRange.getBegin();
                        getRewriter().InsertText(InsertLoc, newInitializer, true, true);
                    }
                }
            }
            TargetForLoops.push_back(ForLoop);
        }
        return true;
    }

private:
    std::vector<ForStmt *> TargetForLoops; // Store for loop statements
};

// Register the mutator
static RegisterMutator<ForLoopInitializerMutator> M(
    "ForLoopInitializerMutator",
    "Replaces for loop initializers with an empty declaration.");