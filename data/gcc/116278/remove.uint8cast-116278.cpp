#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class RemoveUint8Cast : public Mutator, public RecursiveASTVisitor<RemoveUint8Cast> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        TraverseAST(getASTContext());
        // if (CastExpr == nullptr) return false;
        if (CastExprs.empty()) return false;

        auto *CastExpr = randElement(CastExprs);

        // Remove the uint8_t cast
        SourceLocation Start = CastExpr->getBeginLoc();
        SourceLocation End = CastExpr->getSubExpr()->getBeginLoc();
        
        getRewriter().RemoveText(SourceRange(Start, End.getLocWithOffset(-1)));
        
        return true;
    }

    bool VisitCStyleCastExpr(CStyleCastExpr *Cast) {
        // Look for inner uint8_t cast within uint16_t cast
        if (Cast->getType()->isUnsignedIntegerType() && 
            Cast->getSubExpr() && Cast->getSubExpr()->getType()->isUnsignedIntegerType()) {
            if (auto *InnerCast = const_cast<CStyleCastExpr*>(dyn_cast<CStyleCastExpr>(Cast->getSubExpr()))) {
                if (InnerCast->getType()->isSpecificBuiltinType(BuiltinType::UChar)) {
                    // CastExpr = InnerCast;
                    CastExprs.push_back(InnerCast);
                }
            }
        }
        return true;
    }

private:
    // CStyleCastExpr *CastExpr = nullptr;
    std::vector<CStyleCastExpr*> CastExprs;
};

static RegisterMutator<RemoveUint8Cast> M(
    "remove.uint8cast", 
    "Removes unnecessary uint8_t cast from uint16_t cast expression");