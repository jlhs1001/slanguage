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


class Lexer {
public:
    std::string source;
    unsigned int line;

    const char *start;
    const char *current;
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
private:
};


#endif //SLANG_LEXER_H
