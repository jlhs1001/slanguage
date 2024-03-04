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

class Token {
public:
    TokenType type;
    const char *start;
    int length;
    int line;

    Token(
            TokenType type,
            const char *start,
            int length,
            int line
    ) : type(type), start(start), length(length), line(line) {}
};

#endif //SLANG_TOKEN_H
