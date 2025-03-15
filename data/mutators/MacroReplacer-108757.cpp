#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "Mutator.h"
#include "MutatorManager.h"

using namespace clang;

class MacroReplacer : public Mutator, public RecursiveASTVisitor<MacroReplacer> {
public:
    using Mutator::Mutator;
    
    bool mutate() override {
        SM = &getASTContext().getSourceManager();

        auto MainFileID = SM->getMainFileID();
        llvm::StringRef FileData = SM->getBufferData(MainFileID);

        // Find all #define directives
        findSingleLineMacroLocations(FileData);

        if (TargetRanges.empty()) return false;

        SourceRange TargetRange = randElement(TargetRanges);

        getRewriter().ReplaceText(TargetRange, "5");

        TargetRange = randElement(TargetRanges);

        getRewriter().ReplaceText(TargetRange, "3");
        
        return true;
    }

    private:
    SourceManager *SM = nullptr;

    std::vector<SourceRange> TargetRanges;

    void findSingleLineMacroLocations(llvm::StringRef FileData) {
        std::istringstream Stream(FileData.str());
        std::string Line;
        size_t LineNumber = 0;

        while (std::getline(Stream, Line)) {
            LineNumber++;

            // Trim leading spaces
            size_t FirstNonSpace = Line.find_first_not_of(" \t");
            if (FirstNonSpace == std::string::npos)
                continue;

            // Check if the line starts with #define
            if (Line.substr(FirstNonSpace, 7) == "#define") {
                size_t Column = FirstNonSpace + 1;

                // Check if the line is single-line (no continuation character)
                if (Line.back() == '\\') {
                    // llvm::errs() << "Skipping multi-line macro at line: " << LineNumber << "\n";
                    continue;
                }

                // Get SourceLocation
                SourceLocation StartLoc = SM->translateLineCol(SM->getMainFileID(), LineNumber, Column);

                // llvm::errs() << "Single-line macro found at: " << StartLoc.printToString(*SM) << "\n";

                // Extract macro details and value range
                extractMacroDetails(Line, StartLoc, LineNumber);
            }
        }
    }

    void extractMacroDetails(const std::string &Line, clang::SourceLocation StartLoc, size_t LineNumber) {
        std::istringstream LineStream(Line);
        std::string Directive, MacroName, MacroValue;

        LineStream >> Directive; // #define
        LineStream >> MacroName; // Macro name

        // Get the value (rest of the line after the name)
        std::getline(LineStream, MacroValue);
        MacroValue = MacroValue.substr(MacroValue.find_first_not_of(" \t")); // Trim leading spaces

        // Compute the value range
        size_t ValueStartCol = Line.find_first_not_of(" \t", Line.find(MacroName) + MacroName.length());
        size_t ValueEndCol = Line.length();

        SourceLocation ValueStartLoc = SM->translateLineCol(SM->getMainFileID(), LineNumber, ValueStartCol + 1);
        SourceLocation ValueEndLoc = SM->translateLineCol(SM->getMainFileID(), LineNumber, ValueEndCol + 1);

        SourceRange ValueRange(ValueStartLoc, ValueEndLoc);
        TargetRanges.push_back(ValueRange);

        // Print details
        // llvm::errs() << "Macro Name: " << MacroName << "\n";
        // llvm::errs() << "Macro Value: " << MacroValue.trim() << "\n";
        // llvm::errs() << "Macro Value Range: " << ValueRange.printToString(*SM) << "\n";
    }
};

static RegisterMutator<MacroReplacer> X(
    "MacroReplacer",
    "Replaces macro values N=32 with N=5 and M=2 with M=3");