//
// Created by Liam Seewald on 3/6/24.
//

#ifndef SLANG_PARSER_H
#define SLANG_PARSER_H

#include "Lexer.h"
#include "expression/ExpressionNode.h"
#include "expression/NumberNode.h"
#include "expression/BinaryExpressionNode.h"
#include "expression/UnaryExpressionNode.h"
#include "ProgramNode.h"
#include "statement/StatementNode.h"

class Parser {
private:
    Lexer *lexer; // Lexer reference

    Token previousToken; // Previous token
    Token currentToken; // Current token

    void consume(); // Consume function
    void match(TokenType type); // Match function

    std::unique_ptr<ProgramNode> program(); // Program function
    std::unique_ptr<StatementNode> statement(); // Statement function

    std::unique_ptr<ExpressionNode> expression(); // Expression function
    std::unique_ptr<ExpressionNode> term(); // Term function
    std::unique_ptr<ExpressionNode> factor(); // Factor function

    void error(const std::string& message); // Error function
public:
    Parser(Lexer *lexer); // Constructor

    void parse(); // Parse function
};


#endif //SLANG_PARSER_H
