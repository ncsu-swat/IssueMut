#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ReplaceStrcpyWithInitializer : public Mutator,
    public RecursiveASTVisitor<ReplaceStrcpyWithInitializer> {

public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        return modified;
    }

    bool VisitCallExpr(CallExpr *Call) {
        if (const FunctionDecl *Func = Call->getDirectCallee()) {
            if (Func->getNameAsString() == "__builtin_strcpy") {
                // Get the array declaration
                if (const DeclRefExpr *Dest = dyn_cast<DeclRefExpr>(
                    Call->getArg(0)->IgnoreParenCasts())) {
                    
                    if (const VarDecl *Array = dyn_cast<VarDecl>(
                        Dest->getDecl())) {

                        SourceRange StrcpyRange = Call->getSourceRange();
                        SourceLocation ArrayEndLoc = Array->getEndLoc();
                        
                        // Get the string literal arg
                        if (const Expr *Src = Call->getArg(1)) {
                            std::string InitStr = " = ";
                            InitStr += getSourceText(Src);
                            
                            // Add initializer before array declaration end
                            SourceLocation InsertLoc = Lexer::getLocForEndOfToken(
                                ArrayEndLoc, 0, 
                                getRewriter().getSourceMgr(),
                                getASTContext().getLangOpts());

                            getRewriter().InsertText(InsertLoc, InitStr);
                            
                            // Remove the strcpy call and semicolon
                            SourceLocation StrcpyEnd = Lexer::getLocForEndOfToken(
                                StrcpyRange.getEnd(), 0,
                                getRewriter().getSourceMgr(),
                                getASTContext().getLangOpts());

                            getRewriter().RemoveText(
                                CharSourceRange::getCharRange(
                                    StrcpyRange.getBegin(),
                                    StrcpyEnd.getLocWithOffset(1)));

                            modified = true;
                        }
                    }
                }
            }
        }
        return true;
    }

private:
    bool modified = false;

    std::string getSourceText(const Expr *E) {
        SourceRange Range = E->getSourceRange();
        return std::string(Lexer::getSourceText(
            CharSourceRange::getTokenRange(Range),
            getRewriter().getSourceMgr(),
            getASTContext().getLangOpts()));
    }
};

static RegisterMutator<ReplaceStrcpyWithInitializer> X(
    "replace.strcpy",
    "Replaces strcpy with array initializer.");