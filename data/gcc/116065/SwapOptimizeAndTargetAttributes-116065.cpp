#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class SwapOptimizeAndTargetAttributes : public Mutator, public clang::RecursiveASTVisitor<SwapOptimizeAndTargetAttributes> {
public:
    using Mutator::Mutator;

    bool mutate() override {
        // Traverse the AST
        TraverseDecl(getASTContext().getTranslationUnitDecl());
        // If no functions were mutated, return false
        return !MutatedFunctions.empty();
    }

    bool VisitFunctionDecl(FunctionDecl *FD) {
        // Check if the function has attributes
        if (FD->hasAttrs()) {
            SourceManager &SM = getRewriter().getSourceMgr();
            LangOptions LangOpts = getASTContext().getLangOpts();

            // Get the function declaration source range
            SourceRange FuncRange = FD->getSourceRange();
            if (FuncRange.isInvalid())
                return true;

            // Get the source code of the function declaration
            CharSourceRange CharRange = CharSourceRange::getCharRange(FuncRange);
            StringRef FuncCode = Lexer::getSourceText(CharRange, SM, LangOpts);
            if (FuncCode.empty())
                return true;

            // Find the '__attribute__' keyword
            size_t AttrPos = FuncCode.find("__attribute__");
            if (AttrPos == StringRef::npos)
                return true;

            // Find the opening and closing parentheses of the attribute list
            size_t OpenParenPos = FuncCode.find("((", AttrPos);
            if (OpenParenPos == StringRef::npos)
                return true;

            size_t CloseParenPos = findMatchingClosingParen(FuncCode, OpenParenPos + 1);
            if (CloseParenPos == StringRef::npos)
                return true;

            // Extract the attribute list
            size_t AttrListStart = OpenParenPos + 2;
            size_t AttrListLength = CloseParenPos - AttrListStart;
            StringRef AttrListText = FuncCode.substr(AttrListStart, AttrListLength).trim();

            // Split the attributes at top-level commas
            SmallVector<StringRef, 8> Attrs;
            splitAttributesAtTopLevel(AttrListText, Attrs);

            // Find the indices of 'optimize' and 'target' attributes
            int OptimizeIdx = -1;
            int TargetIdx = -1;
            for (unsigned i = 0; i < Attrs.size(); ++i) {
                StringRef AttrTrimmed = Attrs[i].trim();
                if (AttrTrimmed.startswith("optimize")) {
                    OptimizeIdx = i;
                } else if (AttrTrimmed.startswith("target")) {
                    TargetIdx = i;
                }
            }

            // If both attributes are present and 'optimize' comes before 'target', swap them
            if (OptimizeIdx != -1 && TargetIdx != -1 && OptimizeIdx < TargetIdx) {
                // Swap the attributes
                std::swap(Attrs[OptimizeIdx], Attrs[TargetIdx]);

                // Reconstruct the attribute list
                std::string NewAttrList;
                for (unsigned i = 0; i < Attrs.size(); ++i) {
                    if (i > 0)
                        NewAttrList += ", ";
                    NewAttrList += Attrs[i].str();
                }

                // Reconstruct the entire attribute specifier
                std::string NewAttrText = "__attribute__((" + NewAttrList + "))";

                // Calculate the source locations for replacement
                SourceLocation AttrBeginLoc = FuncRange.getBegin().getLocWithOffset(AttrPos);
                SourceLocation AttrEndLoc = FuncRange.getBegin().getLocWithOffset(CloseParenPos + 2);

                CharSourceRange AttrCharRange = CharSourceRange::getCharRange(AttrBeginLoc, AttrEndLoc);

                // Replace the old attribute text with the new attribute text
                getRewriter().ReplaceText(AttrCharRange, NewAttrText);

                // Record that we've mutated this function
                MutatedFunctions.insert(FD);
            }
        }
        return true;
    }

private:
    llvm::SmallPtrSet<FunctionDecl *, 4> MutatedFunctions;

    // Helper function to find the matching closing parenthesis
    size_t findMatchingClosingParen(StringRef Str, size_t OpenPos) {
        int Depth = 1;
        for (size_t i = OpenPos + 1; i < Str.size(); ++i) {
            if (Str[i] == '(') {
                Depth++;
            } else if (Str[i] == ')') {
                Depth--;
                if (Depth == 0)
                    return i;
            }
        }
        return StringRef::npos; // No matching closing parenthesis found
    }

    // Helper function to split attributes at the top level, considering nested parentheses
    void splitAttributesAtTopLevel(StringRef AttrsText, SmallVectorImpl<StringRef> &AttrList) {
        const char *Start = AttrsText.begin();
        const char *Cur = Start;
        const char *End = AttrsText.end();
        int ParenDepth = 0;
        const char *TokenStart = Start;

        while (Cur != End) {
            if (*Cur == '(') {
                ParenDepth++;
            } else if (*Cur == ')') {
                ParenDepth--;
            } else if (*Cur == ',' && ParenDepth == 0) {
                // Found a top-level comma
                AttrList.push_back(StringRef(TokenStart, Cur - TokenStart).trim());
                TokenStart = Cur + 1; // Skip the comma
            }
            ++Cur;
        }

        // Add the last attribute
        if (TokenStart < End) {
            AttrList.push_back(StringRef(TokenStart, End - TokenStart).trim());
        }
    }
};

// Register the mutator
static RegisterMutator<SwapOptimizeAndTargetAttributes> M(
    "SwapOptimizeAndTargetAttributes",
    "Swaps the order of 'optimize' and 'target' attributes in function declarations.");