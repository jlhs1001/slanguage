//
// Created by Liam Seewald on 3/4/24.
//

#ifndef SLANG_TOKEN_H
#define SLANG_TOKEN_H

enum class TokenType {
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals.
    IDENTIFIER, STRING, NUMBER,

    // Keywords.
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    // End of file.
    END_OF_FILE
};

// Defines a Token class that represents lexical tokens in the source code.
// A token is a sequence of characters that form a single, indivisible unit of meaning.
// The Token class encapsulates the type of the token, the start and length of the token in the source code,
class Token {
public:
    // The type of the token, e.g., keyword, identifier, literal, etc.
    TokenType type;
    // A pointer to the start of the token in the source code.
    const char *start;
    // The length of the token in the source code.
    int length;
    // The line number of the token in the source code.
    int line;

    // Constructor for creating a new Token instance.
    // Initializes the token with the specified type, start, length, and line number.
    Token(
            // The type of token.
            TokenType type,
            // A pointer to the start of the token in the source code.
            const char *start,
            // The length of the token in the source code.
            int length,
            // The line number of the token in the source code.
            int line
    ) : type(type), start(start), length(length), line(line) {}
};

#endif //SLANG_TOKEN_H
