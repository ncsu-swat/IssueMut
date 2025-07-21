#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Rewrite/Core/Rewriter.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveConstEmbedInit : public Mutator,
                               public RecursiveASTVisitor<RemoveConstEmbedInit> {
public:
  using Mutator::Mutator;

  bool mutate() override {
    TraverseAST(getASTContext());

    for (auto *VD : EmbedDecls) {
        if (!VD->hasInit()) continue;

        QualType QT = VD->getType();
        const auto *AT = dyn_cast<ArrayType>(QT.getTypePtr());
        if (!AT) continue;
        QualType Elem = AT->getElementType();
        Elem.removeLocalConst();
        std::string ElemType = Elem.getAsString();
        std::string VarName = VD->getNameAsString();

        // Extract the initializer source (e.g. { #embed "..." })
        SourceRange InitRange = VD->getInit()->getSourceRange();
        std::string InitText = getSourceText(InitRange);

        std::string NewCode = ElemType + " *" + VarName + " = (" + ElemType + "[])" + InitText + ";";

        SourceRange DeclRange = VD->getSourceRange();
        SourceLocation Start = getSourceManager().getSpellingLoc(DeclRange.getBegin());
        SourceLocation End = getLocForEndOfToken(DeclRange.getEnd());

        getRewriter().ReplaceText(SourceRange{Start, End}, NewCode);
        mutated = true;
    }

    return mutated;
  }

  bool VisitVarDecl(VarDecl *VD) {
    
    if (!VD->hasInit() || !VD->getType()->isArrayType())
      return true;

    if (!VD->getType().isConstQualified())
      return true;

    SourceRange InitRange = VD->getInit()->getSourceRange();
    if (!InitRange.isValid())
        return true;

    // Optional: heuristic check that init range contains "#embed"
    std::string InitCode = getSourceText(InitRange);
    if (InitCode.find("#embed") == std::string::npos)
        return true;

    // #embed is represented as OpaqueValueExpr or other depending on LLVM version
    EmbedDecls.push_back(VD);
    return true;
  }
  std::string getSourceText(SourceRange range) {
    const auto &SM = getSourceManager();
    clang::LangOptions lopt; // Use actual LangOptions if available
    return clang::Lexer::getSourceText(
        clang::CharSourceRange::getTokenRange(range),
        SM, lopt, nullptr
    ).str();
  }
private:
  std::vector<VarDecl *> EmbedDecls;
  bool mutated = false;
};

static RegisterMutator<RemoveConstEmbedInit> M(
  "remove.const.embed.init",
  "Convert static const arrays with #embed to compound literal pointers"
);