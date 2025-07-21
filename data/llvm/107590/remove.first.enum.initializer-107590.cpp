#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <random>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveFirstEnumInitializer : public Mutator,
                                   public RecursiveASTVisitor<RemoveFirstEnumInitializer> {
public:
  using Mutator::Mutator;

  bool mutate() override {
    TraverseAST(getASTContext());

    if (Enums.empty())
      return false;

    // Randomly select one enum declaration
    EnumDecl *chosenEnum = randElement(Enums);

    // Get the first enumerator
    auto it = chosenEnum->enumerator_begin();
    if (it == chosenEnum->enumerator_end())
      return false;

    EnumConstantDecl *firstEnumConst = *it;
    if (!firstEnumConst->getInitExpr())
      return false; // Already has no initializer

    SourceLocation initStart = firstEnumConst->getInitExpr()->getBeginLoc();
    SourceLocation initEnd = firstEnumConst->getInitExpr()->getEndLoc();

    // Search for '=' token before the initializer
    SourceManager &SM = getASTContext().getSourceManager();
    LangOptions LangOpts = getASTContext().getLangOpts();
    SourceLocation enumEnd = Lexer::getLocForEndOfToken(firstEnumConst->getLocation(), 0, SM, LangOpts);

    // Create range from just after the identifier to the end of the initializer
    CharSourceRange totalRange = CharSourceRange::getCharRange(enumEnd, Lexer::getLocForEndOfToken(initEnd, 0, SM, LangOpts));

    getRewriter().RemoveText(totalRange);

    return true;
  }

  bool VisitEnumDecl(EnumDecl *ED) {
    if (ED->enumerator_begin() != ED->enumerator_end())
        Enums.push_back(ED);
    return true;
  }

private:
  std::vector<EnumDecl *> Enums;
};

static RegisterMutator<RemoveFirstEnumInitializer> M(
  "remove.first.enum.initializer",
  "Removes the initializer from the first field of a randomly selected enum"
);