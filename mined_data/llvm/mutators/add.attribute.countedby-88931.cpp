#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Rewrite/Core/Rewriter.h>

#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class AddAttributeCountedBy : public Mutator,
                              public RecursiveASTVisitor<AddAttributeCountedBy> {
public:
  using Mutator::Mutator;

  bool mutate() override {
    TraverseAST(getASTContext());

    if (Structs.empty()) return false;
    for (RecordDecl *RD : Structs) {
      FieldDecl *lastIntField = nullptr;

      for (auto *FD : RD->fields()) {
        QualType QT = FD->getType();

        if (QT->isIncompleteArrayType()) {
          if (lastIntField && !FD->hasAttrs()) {
            std::string countedAttr = " __attribute__((counted_by(" + lastIntField->getNameAsString() + ")))";
            SourceLocation insertLoc = FD->getEndLoc();
            getRewriter().InsertTextAfterToken(insertLoc, countedAttr);
            mutated = true;
          }
          break;
        }

        if (QT->isIntegerType()) {
          lastIntField = FD;
        }
      }   
    }  
    return mutated;
  }

  bool VisitRecordDecl(RecordDecl *RD) {
    if (!RD->isStruct() || RD->field_empty())
      return true;
    
    Structs.push_back(RD);
    return true;
  }

private:
  std::vector<clang::RecordDecl *> Structs;
  bool mutated = false;
};

static RegisterMutator<AddAttributeCountedBy> M(
  "add.attribute.countedby",
  "Adds __attribute__((counted_by(...))) to flexible array members using the preceding integer field"
);
