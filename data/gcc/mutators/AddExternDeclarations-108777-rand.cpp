#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class AddExternDeclarations : public Mutator, public RecursiveASTVisitor<AddExternDeclarations> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());

        if (FunctionDecls.empty())
            return false;

        // Create a printing policy to control the formatting of types
        PrintingPolicy Policy(getASTContext().getLangOpts());
        Policy.SuppressScope = false;
        Policy.AnonymousTagLocations = false;
        Policy.PolishForDeclaration = true;
        Policy.TerseOutput = false;
        Policy.IncludeNewlines = false;
        Policy.SuppressTagKeyword = false;

        // Get the string representation of size_t to replace it with __SIZE_TYPE__
        QualType SizeType = getASTContext().getSizeType();
        std::string SizeTypeStr = SizeType.getAsString(Policy);

        std::vector<const FunctionDecl *> FunctionDeclVector(FunctionDecls.begin(), FunctionDecls.end());

        // Select a random union declaration to modify
        const FunctionDecl *FD = randElement(FunctionDeclVector);
        
        // Generate the extern declaration
        std::string DeclStr = "extern ";

        // Get the return type
        QualType RT = FD->getReturnType();
        DeclStr += RT.getAsString(Policy) + " ";

        // Add function name
        DeclStr += FD->getNameAsString();

        // Add parameters
        DeclStr += " (";
        bool first = true;
        for (const ParmVarDecl *Param : FD->parameters()) {
            if (!first)
                DeclStr += ", ";
            else
                first = false;

            QualType ParamType = Param->getOriginalType();
            DeclStr += ParamType.getAsString(Policy);
        }
        DeclStr += ");\n";

        // Replace size type string with __SIZE_TYPE__
        size_t pos = 0;
        while ((pos = DeclStr.find(SizeTypeStr, pos)) != std::string::npos) {
            DeclStr.replace(pos, SizeTypeStr.length(), "__SIZE_TYPE__");
            pos += std::string("__SIZE_TYPE__").length();
        }

        // Insert at the beginning of the main file
        SourceManager &SM = getSourceManager();
        FileID MainFileID = SM.getMainFileID();
        SourceLocation StartLoc = SM.getLocForStartOfFile(MainFileID);

        if (StartLoc.isInvalid())
            return false;

        getRewriter().InsertTextBefore(StartLoc, DeclStr);

        return true;
    }

    bool VisitCallExpr(CallExpr *Call) {
        if (FunctionDecl *FD = Call->getDirectCallee()) {
            // Check if the function is implicitly declared and global
            if (FD->isImplicit() && FD->isGlobal()) {
                FunctionDecls.insert(FD->getCanonicalDecl());
            }
        }
        return true;
    }

private:
    std::set<const FunctionDecl *> FunctionDecls;
};

// Register the mutator
static RegisterMutator<AddExternDeclarations> M(
    "AddExternDeclarations.rand",
    "Adds extern declarations for functions called in the code.");