#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include "MutatorUsingBash.h"
#include <fstream>
#include <iostream>
#include <unistd.h> // For mkstemp

using namespace clang;

std::string MutatorUsingBash::createTempFile(const std::string& content) {
    // Create a template for mkstemp (must end with "XXXXXX")
    char tempFileName[] = "/tmp/tempfileXXXXXX";

    // mkstemp generates a unique filename and opens the file securely
    int fd = mkstemp(tempFileName);

    if (fd == -1) {
        llvm::outs() << "Failed to create a temporary file.\n";
        return "";
    }

    // llvm::outs() << "Temporary file created: " << tempFileName << "\n";

    // Write to the file
    std::ofstream tempFile(tempFileName);
    if (tempFile.is_open()) {
        tempFile << content;
        tempFile.close();
    } else {
        llvm::outs() << "Failed to open temporary file.\n";
    }

    // Close the file descriptor
    close(fd);

    return std::string(tempFileName);
}

std::string MutatorUsingBash::readFile(const std::string& fileName) {
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
    if (!file) {
        llvm::outs() << "Failed to open file: " << fileName << "\n";
        return "";
    }

    // Read the entire file content into a string
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

bool MutatorUsingBash::replaceAll(std::string pattern, std::string replacement) {
    SourceManager *SM = &getASTContext().getSourceManager();

    auto MainFileID = SM->getMainFileID();
    llvm::StringRef FileData = SM->getBufferData(MainFileID);

    std::string EntireFileContent = FileData.str();

    // Create a temporary file
    std::string tempFileName = createTempFile(EntireFileContent);

    // Run bash command on the string
    std::string bashCommand = "sed -i -E \'s/" + pattern + "/" + replacement + "/\' \"" + tempFileName + "\" 2>/dev/null";
    // llvm::outs() << "bashCommand: " << bashCommand << "\n";

    bool result = runBash(bashCommand);
    if (result == false) {
        std::remove(tempFileName.c_str());
        return false;
    }

    std::string output = readFile(tempFileName);
    if (output == "") {
        std::remove(tempFileName.c_str());
        return false;
    }

    // Remove the temporary file
    std::remove(tempFileName.c_str());

    // Get the start and end SourceLocations of the file
    SourceLocation StartLoc = SM->getLocForStartOfFile(MainFileID);
    SourceLocation EndLoc = SM->getLocForEndOfFile(MainFileID);

    // Construct a SourceRange
    SourceRange FileRange(StartLoc, EndLoc);

    getRewriter().ReplaceText(FileRange, output);
    return true;
}

bool MutatorUsingBash::replaceOne(std::string pattern, std::string replacement) {
    SourceManager *SM = &getASTContext().getSourceManager();

    auto MainFileID = SM->getMainFileID();
    llvm::StringRef FileData = SM->getBufferData(MainFileID);

    std::string EntireFileContent = FileData.str();

    // Create a temporary file
    std::string tempFileName = createTempFile(EntireFileContent);

    // Run bash command on the string
    std::string bashCommand = "bash ~/MetaMut/mutators/replaceOne.sh " + tempFileName + " \'" + pattern + "\' \'" + replacement + "\' " + std::to_string(getSeed()) + " 2>/dev/null";
    
    // llvm::outs() << "bashCommand: " << bashCommand << "\n";
    bool result = runBash(bashCommand);
    if (result == false) {
        std::remove(tempFileName.c_str());
        return false;
    }

    std::string output = readFile(tempFileName);
    if (output == "") {
        std::remove(tempFileName.c_str());
        return false;
    }
    
    // Remove the temporary file
    std::remove(tempFileName.c_str());

    // Get the start and end SourceLocations of the file
    SourceLocation StartLoc = SM->getLocForStartOfFile(MainFileID);
    SourceLocation EndLoc = SM->getLocForEndOfFile(MainFileID);

    // Construct a SourceRange
    SourceRange FileRange(StartLoc, EndLoc);

    getRewriter().ReplaceText(FileRange, output);
    return true;
}

bool MutatorUsingBash::replaceWithBashScript(std::string bashFileName) {
    SourceManager *SM = &getASTContext().getSourceManager();

    auto MainFileID = SM->getMainFileID();
    llvm::StringRef FileData = SM->getBufferData(MainFileID);

    std::string EntireFileContent = FileData.str();

    // Create a temporary file
    std::string tempFileName = createTempFile(EntireFileContent);

    // Run bash command on the string
    std::string bashCommand = "bash " + bashFileName + " " + tempFileName + " " + std::to_string(getSeed()) +" 2>/dev/null";
    // llvm::outs() << "bashCommand: " << bashCommand << "\n";
    bool result = runBash(bashCommand);
    if (result == false) {
        std::remove(tempFileName.c_str());
        return false;
    }

    std::string output = readFile(tempFileName);
    if (output == "") {
        std::remove(tempFileName.c_str());
        return false;
    }
    
    // Remove the temporary file
    std::remove(tempFileName.c_str());

    // Get the start and end SourceLocations of the file
    SourceLocation StartLoc = SM->getLocForStartOfFile(MainFileID);
    SourceLocation EndLoc = SM->getLocForEndOfFile(MainFileID);

    // Construct a SourceRange
    SourceRange FileRange(StartLoc, EndLoc);

    getRewriter().ReplaceText(FileRange, output);
    return true;
}

bool MutatorUsingBash::runBash(const std::string& bashCommand) {
    
    // Open a pipe to read the output
    std::array<char, 128> buffer;
    std::string result;
    FILE* pipe = popen(bashCommand.c_str(), "r");

    if (!pipe) {
        std::cerr << "Failed to run bash command." << std::endl;
        return false;
    }

    // Read the output from the pipe
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    // Get the exit code of the command
    int exitCode = pclose(pipe);

    // Check if the exit code is non-zero
    if (WIFEXITED(exitCode) && WEXITSTATUS(exitCode) != 0) {
        std::cerr << "Command failed with exit code: " << WEXITSTATUS(exitCode) << std::endl;
        return false;
    }

    // Remove trailing newline from the result
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }

    // llvm::outs() << "bash result: " << result << "\n";

    return true;
}