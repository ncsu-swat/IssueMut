#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ChangeFunctionParameter : public Mutator, public clang::RecursiveASTVisitor<ChangeFunctionParameter> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());

        return !TargetPairs.empty() && applyMutation(randElement(TargetPairs));
    }

    bool VisitFunctionDecl(FunctionDecl *FuncDecl) {
        // Identify the target function 'sumxy_p'
        // if (FuncDecl->getName() == "sumxy_p" && FuncDecl->getNumParams() == 1) {
            // TargetFunctions.push_back(FuncDecl);
        // }
        for (unsigned i = 0; i < FuncDecl->getNumParams(); i++) {
            ParmVarDecl *ParamDecl = FuncDecl->getParamDecl(i);
            std::string TypeName = ParamDecl->getType().getAsString();
            if (TypeName.find("*") != std::string::npos) {
                TargetPairs.push_back(std::make_pair(FuncDecl, ParamDecl));
            }
        }

        return true;
    }
    
private:
    std::vector<FunctionDecl *> TargetFunctions;

    std::vector<std::pair<FunctionDecl *, ParmVarDecl *>> TargetPairs;

    bool applyMutation(std::pair<FunctionDecl *, ParmVarDecl *>TargetPair) {
        
        FunctionDecl *FuncDecl = TargetPair.first;
        ParmVarDecl *Param = TargetPair.second;
        // const ParmVarDecl *Param = FuncDecl->getParamDecl(0);
        // if (!Param) return false;

        // Get locations to replace the parameter type
        SourceLocation StartLoc = Param->getBeginLoc();
        SourceLocation EndLoc = Param->getEndLoc();

        std::string ParamDeclString = getText(SourceRange(StartLoc, EndLoc));
        // llvm::outs() << "Param: " << getText(SourceRange(StartLoc, EndLoc)) << "\n";
        
        // Define new type
        std::string NewParamDeclString = ParamDeclString;
        size_t pos = NewParamDeclString.find("const");
        if (pos != std::string::npos) {
            // Replace the substring
            NewParamDeclString.replace(pos, 5, "");
        }
        pos = NewParamDeclString.find("*");
        if (pos != std::string::npos) {
            // Replace the substring
            NewParamDeclString.replace(pos, 1, "");
        }

        // llvm::outs() << "New Param: " << NewParamDeclString << "\n";

        // std::string OldType = "const P2d* "; // Original type to be replaced

        // Replace 'const P2d*' with 'P2d '
        getRewriter().ReplaceText(StartLoc, ParamDeclString.length(), NewParamDeclString);

        // Change the body to access members as p.x instead of p->x
        if (FuncDecl->getBody()) {
            std::string OldMemberAccess = std::string(Param->getName()) + "->"; // e.g., "p->"
            std::string NewMemberAccess = std::string(Param->getName()) + "."; // e.g., "p."

            SourceLocation FunctionBodyStart = FuncDecl->getBody()->getBeginLoc();
            SourceLocation FunctionBodyEnd = FuncDecl->getBody()->getEndLoc();
            CharSourceRange BodyRange = CharSourceRange::getCharRange(FunctionBodyStart, FunctionBodyEnd);

            // Get the body of the function as a string
            llvm::StringRef FunctionBodyText = Lexer::getSourceText(BodyRange, 
                getRewriter().getSourceMgr(), getASTContext().getLangOpts());

            // Replace occurrences of "p->" with "p."
            std::string UpdatedBody = FunctionBodyText.str(); // Convert to std::string
            size_t pos = UpdatedBody.find(OldMemberAccess);
            while (pos != std::string::npos) {
                UpdatedBody.replace(pos, OldMemberAccess.length(), NewMemberAccess);
                pos = UpdatedBody.find(OldMemberAccess, pos + NewMemberAccess.length());
            }

            // Replace the entire body with the updated version
            getRewriter().ReplaceText(FunctionBodyStart, FunctionBodyText.size(), UpdatedBody);
        }

        return true;
    }

    std::string getText(SourceRange Range) {
        return Lexer::getSourceText(
            CharSourceRange::getTokenRange(Range),
            getASTContext().getSourceManager(),
            getASTContext().getLangOpts()).str();
    }
};

// Register the mutator
static RegisterMutator<ChangeFunctionParameter> M(
    "ChangeFunctionParameter",
    "Changes parameter type of function from 'const XX*' to 'XX'.");