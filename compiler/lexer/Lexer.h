//
// Created by Liam Seewald on 3/4/24.
//

#ifndef SLANG_LEXER_H
#define SLANG_LEXER_H
#include <string>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


// Represents the lexical analyzer for the slang compiler.
// The Lexer class is responsible for converting a sequence of source characters
// into a sequence of tokens. These tokens are then used by the parser to build
// an abstract syntax tree (AST) that represents the structure of the source code.
class Lexer {
public:
    // Holds the entire source code as a string.
    std::string source;

    // The current line number in the source code.
    unsigned int line;

    // I'm going to make start an iterator.
    std::string::const_iterator lexemeStart;
    std::string::const_iterator current;
public:
    // Reads the entire contents of a file into a string.
    //
    // This method utilizes the C++ Standard Library to read the contents of a file
    // specified by its path. It is designed to read the file in binary mode to ensure
    // that the data is read exactly as it is stored, without any transformations that
    // might be applied in text mode.
    //
    // Parameters:
    //  path - The path to the file to be read.
    //
    // Returns:
    //  A string containing the entire contents of the file.
    //
    // Throws:
    //  std::runtime_error - If the file could not be opened. The exception message
    //  contains the path to aid in debugging the cause of the error.
    //
    // Example Usage:
    //  std::string source = Lexer::readFile("path/to/file.sl");
    //
    static std::string readFile(const std::string &path);
public:
    explicit Lexer(const std::string& sourcePath);
    ~Lexer();

    char advance();
    bool match(char expected);
    [[nodiscard]] char peek() const;
    [[nodiscard]] char peekNext() const;
private:
};


#endif //SLANG_LEXER_H
