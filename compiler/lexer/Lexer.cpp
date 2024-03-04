//
// Created by Liam Seewald on 3/4/24.
//

#include "Lexer.h"
#include <iostream>

std::string Lexer::readFile(const std::string &path) {
    // Open the file in binary mode and position the file pointer at the end to obtain its size.
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) {
        // If the file could not be opened, throw an exception with the path to aid in debugging.
        throw std::runtime_error("Could not open file at " + path);
    }

    // Move the file pointer to the beginning of the file before reading its contents.
    file.seekg(0, std::ios::beg);

    // Initialize a string with two iterators, reading the entire file contents into the string.
    // The first iterator is the beginning of the file, and the second represents the EOF marker.
    return {
            (std::istreambuf_iterator<char>(file)),
            (std::istreambuf_iterator<char>())
    };
}

Lexer::Lexer(const std::string& sourcePath) {
    // Load the source code from the file into a string.
    source = readFile(sourcePath);
}

char Lexer::advance() {
    current++;
    return current[-1];
}

Lexer::~Lexer() = default;
