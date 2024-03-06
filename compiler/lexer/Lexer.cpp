//
// Created by Liam Seewald on 3/4/24.
//
// TODO: Add informative comments to the implementation file.
#include "Lexer.h"
#include "Utils.h"
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

Token Lexer::makeToken(TokenType type) const {
    return {
        type,
        lexemeStart,
        static_cast<int>(current - lexemeStart),
        line
    };
}

Lexer::Lexer(const std::string& sourcePath) {
    // Load the source code from the file into a string.
    source = readFile(sourcePath);

    // Initialize the line number to 1 and the current
    // character to the beginning of the source code.
    line = 1;
    lexemeStart = source.begin();

    // Set the current iterator to the beginning of the source code.
    current = source.begin();
}

char Lexer::advance() {
    current++;
    return current[-1];
}

bool Lexer::match(char expected) {
    if (IS_EOF(*current) || *current != expected) return false;

    current++;
    return true;
}

inline char Lexer::peek() const {
    return *current;
}

char Lexer::peekNext() const {
    if (IS_EOF(*current)) return '\0';
    return current[1];
}

inline void Lexer::skipWhitespace() {
    for (;;) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                line++;
                advance();
                break;
            case '/':
                if (peekNext() == '/') {
                    while (peek() != '\n' && !IS_EOF(peek())) advance();
                } else if (peekNext() == '*') {
                    advance();
                    advance();
                    while (peek() != '*' && peekNext() != '/' && !IS_EOF(peek())) {
                        if (peek() == '\n') line++;
                        advance();
                    }
                    if (IS_EOF(peek())) {
                        std::cerr << "Unterminated block comment at line " << line << std::endl;
                    } else {
                        advance();
                        advance();
                    }
                } else {
                    return;
                }
                break;
            default:
                return;
        }
    }
}

Token Lexer::getNextToken() {
    // Skip over any whitespace characters in the source code.
    skipWhitespace();

    // Set the start of the lexeme to the current character.
    lexemeStart = current;

    // If the current character is the end of the source code, return an EOF token.
    if (IS_EOF(*current)) return Token{TokenType::END_OF_FILE, lexemeStart, 0, line};

    // Advance the current character to the next character in the source code.
    char c = advance();

    // Lex identifiers
    if (IS_VALID_ID(c)) {
        // Consume the rest of the identifier.
        while (IS_VALID_ID(peek()) || IS_DIGIT(peek())) advance();

        // Return the token for the identifier.
        return makeToken(identifierType());
    }

    // Lex numeric literals
    if (IS_DIGIT(c)) {
        // TODO: For the sake of consistency, perhaps split this into a separate function.
        //  However, this is a simple enough case that it's not necessary. Eventually, the lexer
        //  will support hex literals, scientific notation, and other numeric formats.

        // Consume the rest of the numeric literal.
        while (IS_DIGIT(peek())) advance();

        // Look for a decimal point.
        if (peek() == '.' && IS_DIGIT(peekNext())) {
            // Consume the '.'.
            advance();

            // Consume the rest of the numeric literal.
            while (IS_DIGIT(peek())) advance();
        }

        // Return the token for the numeric literal.
        return makeToken(TokenType::NUMBER);
    }

    // Lex single-character tokens
    switch (c) {
        case '(':
            return makeToken(TokenType::LEFT_PAREN);
        case ')':
            return makeToken(TokenType::RIGHT_PAREN);
        case '{':
            return makeToken(TokenType::LEFT_BRACE);
        case '}':
            return makeToken(TokenType::RIGHT_BRACE);
        case ',':
            return makeToken(TokenType::COMMA);
        case '.':
            return makeToken(TokenType::DOT);
        case '-':
            return makeToken(TokenType::MINUS);
        case '+':
            return makeToken(TokenType::PLUS);
        case ';':
            return makeToken(TokenType::SEMICOLON);
        case '*':
            return makeToken(TokenType::STAR);
        case '!':
            return makeToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        case '=':
            return makeToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        case '<':
            return makeToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        case '>':
            return makeToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        case '/':
            return makeToken(TokenType::SLASH);
        case '"':
            return string();
        default:
            break;
    }
}

TokenType Lexer::identifierType() {
    // This is a bit unorthodox in manner of appearance, bit it's a simple DFA
    // that determines the type of the identifier based on its lexeme.

    // Cache the first and second characters of the lexeme.
    // Based on the slang grammar, only the first two characters are needed to determine the type.
    char first = lexemeStart[0];
    char second = lexemeStart[1];

    // check if the identifier is a keyword
    switch (first) {
        case 'a':
            return checkKeyword(1, 2, "nd", TokenType::AND);
        case 'c':
            return checkKeyword(1, 4, "lass", TokenType::CLASS);
        case 'e':
            return checkKeyword(1, 3, "lse", TokenType::ELSE);
        case 'f':
            if (current - lexemeStart > 1) {
                switch (second) {
                    case 'n':
                        return checkKeyword(2, 1, "n", TokenType::FN);
                    case 'o':
                        return checkKeyword(2, 1, "r", TokenType::FOR);
                    case 'a':
                        return checkKeyword(2, 3, "lse", TokenType::FALSE);
                }
            }
            break;
        case 'i':
            if (current - lexemeStart > 1) {
                switch (second) {
                    case 'f':
                        return checkKeyword(2, 0, "", TokenType::IF);
                    case 'n':
                        return checkKeyword(2, 0, "", TokenType::IN);
                }
            }
        case 'l':
            return checkKeyword(1, 2, "et", TokenType::LET);
        case 'n':
            return checkKeyword(1, 3, "ull", TokenType::NIL);
        case 'o':
            return checkKeyword(1, 1, "r", TokenType::OR);
        case 'p':
            return checkKeyword(1, 6, "rintln", TokenType::PRINTLN);
        case 'r':
            return checkKeyword(1, 5, "eturn", TokenType::RETURN);
        case 's':
            if (current - lexemeStart > 1) {
                switch (second) {
                    case 'u':
                        return checkKeyword(2, 4, "per", TokenType::SUPER);
                    case 'e':
                        return checkKeyword(2, 2, "lf", TokenType::SELF);
                }
            }
            break;
        case 't':
            return checkKeyword(1, 3, "rue", TokenType::TRUE);
        case 'w':
            return checkKeyword(1, 4, "hile", TokenType::WHILE);
    }

    return TokenType::IDENTIFIER;
}

Token Lexer::string() {
    while (peek() != '"' && !IS_EOF(peek())) {
        if (peek() == '\n') line++;
        advance();
    }

    if (IS_EOF(peek())) {
        std::cerr << "Unterminated string at line " << line << std::endl;
        return makeToken(TokenType::END_OF_FILE);
    }

    advance();
    return makeToken(TokenType::STRING);
}

TokenType Lexer::checkKeyword(int start, int length, const std::string &rest, TokenType type) {
    if (current - lexemeStart == start + length &&
        std::equal(lexemeStart + start, lexemeStart + start + length, rest.begin())) {
        return type;
    }

    return TokenType::IDENTIFIER;
}

Lexer::~Lexer() = default;
