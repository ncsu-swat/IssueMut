#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ReplaceSizeT : public Mutator, public RecursiveASTVisitor<ReplaceSizeT> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        if (Locations.empty()) return false;

        // for (const auto &loc : Locations) {
        const auto &loc = randElement(Locations);
            getRewriter().ReplaceText(loc.first, loc.second, "int");
        // }
        return true;
    }

    bool VisitTypeLoc(TypeLoc TL) {
        if (auto TTL = TL.getAs<TypedefTypeLoc>()) {
            if (TTL.getTypedefNameDecl()->getNameAsString() == "size_t") {
                SourceLocation Loc = TTL.getBeginLoc();
                unsigned Length = Lexer::MeasureTokenLength(Loc,
                    getRewriter().getSourceMgr(),
                    getASTContext().getLangOpts());
                Locations.push_back(std::make_pair(Loc, Length));
            }
        }
        return true;
    }

private:
    std::vector<std::pair<SourceLocation, unsigned>> Locations;
};

static RegisterMutator<ReplaceSizeT> M(
    "replace.sizet", 
    "Replaces size_t type with int.");