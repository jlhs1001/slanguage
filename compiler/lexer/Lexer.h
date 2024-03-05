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
    std::string source; // Holds the entire source code as a string.
    unsigned int line; // The current line number in the source code.

    // An iterator pointing to the beginning of the current lexeme.
    std::string::const_iterator lexemeStart;
    // An iterator that advances through the source code.
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
    // Constructs a Lexer instance with the source code from the specified file.
    // The source code is read from the specified path, and lexical analysis begins from
    // the start of this source code.
    //
    // Parameters:
    //  sourcePath - A string specifying the path to the source code file.
    explicit Lexer(const std::string& sourcePath);

    // Destructor for the Lexer class.
    ~Lexer();

    // Advances the current iterator to the next character in the source code and returns
    // the current character. This method is used to move through the source code one character
    // at a time, and is used to implement the lexical analysis process.
    char advance();

    // Checks if the current character matches the specified character If so, the current iterator
    // is advanced, and true is returned. Otherwise, the method returns false and the current iterator
    // is not advanced. This method is useful for recognizing multi-character tokens,
    // such as '!=' or '==', or specific patterns in the source code.
    //
    // Parameters:
    //  expected - The character to match against the current character in the source code.
    //
    // Returns:
    //  True if the current character matches the specified character, false otherwise.
    bool match(char expected);

    // Returns the current character in the source code without advancing the current iterator.
    // This method is used to look ahead at the next character in the source code without consuming it,
    // which is useful for recognizing multi-character tokens or specific patterns in the source code.
    [[nodiscard]] char peek() const;

    // Returns the next character in the source code without advancing the current iterator.
    // This method is used to look ahead at the character after the current character in the source code
    // without consuming it, supporting more complex lexical analysis requirements.
    [[nodiscard]] char peekNext() const;

private:
};


#endif //SLANG_LEXER_H
