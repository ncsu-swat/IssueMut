#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeMinusZeroValue : public Mutator, public RecursiveASTVisitor<ChangeMinusZeroValue> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        // If we found variable declarations to modify, finalize the changes
        return finalize();
    }

    bool VisitVarDecl(VarDecl *Decl) {
        // Check for 'minuszero' declaration
        if (/*Decl->getName() == "minuszero" && */
            Decl->hasInit() && 
            Decl->getInit()->getType()->isFloatingType()) {
            // Check if the initialization is `0.0` (not `0`)
            auto *FloatLiteral = dyn_cast<FloatingLiteral>(Decl->getInit());
            if (FloatLiteral && FloatLiteral->getValue().convertToDouble() == 0.0) {
                TargetVariableDecls.push_back(Decl);
            }
        }
        return true;
    }

    bool finalize() {
        for (VarDecl *Decl : TargetVariableDecls) {
            // Get the location of the initializer
            SourceLocation InitLoc = Decl->getInit()->getBeginLoc();
            SourceLocation EndLoc = Decl->getInit()->getEndLoc();

            // Generate the new initialization string
            std::string NewInit = "-0.";
            getRewriter().ReplaceText(SourceRange(InitLoc, EndLoc), NewInit);
        }
        return !TargetVariableDecls.empty(); // Return true if any changes were made
    }

private:
    std::vector<VarDecl*> TargetVariableDecls;
};

// Register the mutator
static RegisterMutator<ChangeMinusZeroValue> M(
    "ChangeMinusZeroValue",
    "Changes the initialization of 'minuszero' from '0.' to '-0.'");