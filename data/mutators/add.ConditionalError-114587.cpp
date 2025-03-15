#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class ConditionalErrorMutator : public Mutator, public RecursiveASTVisitor<ConditionalErrorMutator> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {

        SM = &getASTContext().getSourceManager();

        auto MainFileID = SM->getMainFileID();
        llvm::StringRef FileData = SM->getBufferData(MainFileID);

        // Find all #define directives
        findTargetMacroLocations(FileData);

        if (TargetPairs.empty()) return false;

        auto Target = randElement(TargetPairs);
        std::string macroName = Target.first;
        SourceLocation targetLocation = Target.second;

        getRewriter().InsertTextAfter(targetLocation, "# error "+macroName+" not defined\n");
        return true;
    }

private:
    std::vector<std::pair<std::string, SourceLocation>> TargetPairs;

    SourceManager *SM = nullptr;

    void findTargetMacroLocations(llvm::StringRef FileData) {
        std::istringstream Stream(FileData.str());
        std::string Line;
        size_t LineNumber = 0;

        while (std::getline(Stream, Line)) {
            LineNumber++;

            // Trim leading spaces
            size_t FirstNonSpace = Line.find_first_not_of(" \t");
            if (FirstNonSpace == std::string::npos)
                continue;

            // Check if the line starts with #ifndef
            if (Line.substr(FirstNonSpace, 7) == "#ifndef") {

                std::string MacroName = Line.substr(Line.find_first_not_of(" \t", 7));

                // // Get the start location of the next line
                SourceLocation EndLoc = SM->translateLineCol(SM->getMainFileID(), LineNumber+1, 1);
                
                // Save results for further processing
                TargetPairs.push_back({MacroName, EndLoc});
            }
        }
    }
};

static RegisterMutator<ConditionalErrorMutator> M(
    "add.ConditionalError", 
    "Replaces variable declarations in ifndef with error directive.");
