#ifndef MUTATOR_USING_BASH_H
#define MUTATOR_USING_BASH_H

#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include <string>
#include <array>
#include <iostream>
#include "Mutator.h"

using namespace clang;

class MutatorUsingBash : public Mutator {
public:
    using Mutator::Mutator;

    MutatorUsingBash(const char* name, const char* desc)
        : Mutator(name, desc) {
        // Additional initialization (if needed)
    }

    /**
     * Replaces all occurrences of a pattern in the input string with a replacement string.
     * @param pattern The pattern to replace.
     * @param replacement The replacement string.
     * @return True if the replacement was successful, false otherwise.
     */
    bool replaceAll(std::string pattern, std::string replacement);

    /**
     * Replaces the random occurrence of a pattern in the input string with a replacement string.
     * @param pattern The pattern to replace.
     * @param replacement The replacement string.
     * @return True if the replacement was successful, false otherwise.
     */
    bool replaceOne(std::string pattern, std::string replacement);

    /**
     * Replaces the random occurrence of a pattern in the input string with a bash script.
     * @param bashFileName The bash script file name.
     * @return True if the replacement was successful, false otherwise.
     */
    bool replaceWithBashScript(std::string bashFileName);

private:
    /**
     * Runs a bash command.
     * @param bashCommand The bash command to execute.
     * @return True if the bash command was successful, false otherwise.
     */
    bool runBash(const std::string& bashCommand);
    std::string createTempFile(const std::string& content);
    std::string readFile(const std::string& fileName);
};

#endif // MUTATOR_USING_BASH_H