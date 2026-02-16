#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ConvertVectorFloatToFloat16 : public Mutator, public RecursiveASTVisitor<ConvertVectorFloatToFloat16> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        TraverseAST(getASTContext());
        if (TargetVars.empty()) return false;

        // Randomly select a variable to modify
        VarDecl *Var = randElement(TargetVars);

        // Perform the conversion
        convertFloatToFloat16(Var);

        return true;
    }

    bool VisitVarDecl(VarDecl *Decl) {
        // Check if the variable has a vector type
        QualType Type = Decl->getType();

        if (const auto *VecType = Type->getAs<VectorType>()) {
            if (VecType->getElementType()->isSpecificBuiltinType(BuiltinType::Float)) {
                TargetVars.push_back(Decl);
            }
        }

        return true;
    }

private:
    std::vector<VarDecl *> TargetVars;

    // Convert float vector type to _Float16 vector type
    void convertFloatToFloat16(VarDecl *Var) {
        SourceManager &SM = getRewriter().getSourceMgr();
        const LangOptions &LangOpts = getASTContext().getLangOpts();

        // Get the source range of the type
        QualType Type = Var->getType();
        const auto *VecType = Type->getAs<VectorType>();
        if (!VecType) return;

        SourceLocation StartLoc = Var->getBeginLoc();
        if (StartLoc.isInvalid()) return;

        // Get the type text from the source
        CharSourceRange TypeRange = CharSourceRange::getTokenRange(
            Var->getSourceRange().getBegin(), Lexer::getLocForEndOfToken(StartLoc, 0, SM, LangOpts));

        std::string OriginalType = Lexer::getSourceText(TypeRange, SM, LangOpts).str();

        // Replace 'float' with '_Float16' in the original type text
        std::string UpdatedType = OriginalType;
        size_t Pos = UpdatedType.find("float");
        if (Pos != std::string::npos) {
            UpdatedType.replace(Pos, 5, "_Float16");
        }

        // Replace the type in the source code
        getRewriter().ReplaceText(TypeRange, UpdatedType);
    }
};

// Register the mutator
static RegisterMutator<ConvertVectorFloatToFloat16> M(
    "ConvertVectorFloatToFloat16",
    "Converts float vector types with __attribute__((__vector_size__)) to _Float16 vector types with the same attribute.");