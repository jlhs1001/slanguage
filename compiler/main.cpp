#include <iostream>
#include "lexer/Lexer.h"

std::string getTokenTypeName(TokenType type) {
    switch (type) {
        case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE:
            return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE:
            return "RIGHT_BRACE";
        case TokenType::COMMA:
            return "COMMA";
        case TokenType::DOT:
            return "DOT";
        case TokenType::MINUS:
            return "MINUS";
        case TokenType::PLUS:
            return "PLUS";
        case TokenType::SEMICOLON:
            return "SEMICOLON";
        case TokenType::SLASH:
            return "SLASH";
        case TokenType::STAR:
            return "STAR";
        case TokenType::BANG:
            return "BANG";
        case TokenType::BANG_EQUAL:
            return "BANG_EQUAL";
        case TokenType::EQUAL:
            return "EQUAL";
        case TokenType::EQUAL_EQUAL:
            return "EQUAL_EQUAL";
        case TokenType::GREATER:
            return "GREATER";
        case TokenType::GREATER_EQUAL:
            return "GREATER_EQUAL";
        case TokenType::LESS:
            return "LESS";
        case TokenType::LESS_EQUAL:
            return "LESS_EQUAL";
        case TokenType::IDENTIFIER:
            return "IDENTIFIER";
        case TokenType::STRING:
            return "STRING";
        case TokenType::NUMBER:
            return "NUMBER";
        case TokenType::AND:
            return "AND";
        case TokenType::CLASS:
            return "CLASS";
        case TokenType::ELSE:
            return "ELSE";
        case TokenType::FALSE:
            return "FALSE";
        case TokenType::FN:
            return "FN";
        case TokenType::FOR:
            return "FOR";
        case TokenType::IF:
            return "IF";
        case TokenType::NIL:
            return "NIL";
        case TokenType::OR:
            return "OR";
        case TokenType::PRINTLN:
            return "PRINTLN";
        case TokenType::RETURN:
            return "RETURN";
        case TokenType::SUPER:
            return "SUPER";
        case TokenType::SELF:
            return "SELF";
        case TokenType::TRUE:
            return "TRUE";
        case TokenType::LET:
            return "LET";
        case TokenType::WHILE:
            return "WHILE";
        case TokenType::IN:
            return "IN";
        case TokenType::END_OF_FILE:
            return "END_OF_FILE";
        default:
            return "UNKNOWN";
    }
}

int main() {
    Lexer lexer("../tests/main.sl");
//    lexer.advance();

//    std::cout << *lexer.current << std::endl;
    std::cout << getTokenTypeName(lexer.getNextToken().type) << std::endl;
    std::cout << getTokenTypeName(lexer.getNextToken().type) << std::endl;
    std::cout << getTokenTypeName(lexer.getNextToken().type) << std::endl;

    std::cout << lexer.source << std::endl;
}