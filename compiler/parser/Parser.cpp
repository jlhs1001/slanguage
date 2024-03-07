//
// Created by Liam Seewald on 3/6/24.
//

#include "Parser.h"
#include "expression/BinaryExpressionNode.h"
#include "statement/PrintNode.h"
#include "IRGenerator.h"
#include <iostream>
#include <string>

Parser::Parser(Lexer *lexer) : lexer(lexer) {
    currentToken = lexer->getNextToken();
    previousToken = currentToken;
}

void Parser::consume() {
    previousToken = currentToken;
    currentToken = lexer->getNextToken();
}

void Parser::match(TokenType type) {
    if (currentToken.type == type) {
        consume();
    } else {
        error("Unexpected token");
    }
}

std::unique_ptr<ProgramNode> Parser::program() {
    std::vector<std::unique_ptr<StatementNode>> statements;

    while (currentToken.type != TokenType::END_OF_FILE) {
        statements.push_back(statement());
    }

    return std::make_unique<ProgramNode>(std::move(statements));
}

std::unique_ptr<ExpressionNode> Parser::expression() {
    // Parse terms and handle addition and subtraction
    std::unique_ptr<ExpressionNode> node = term();

    while (currentToken.type == TokenType::PLUS || currentToken.type == TokenType::MINUS) {
        Token op = currentToken;
        consume();
        node = std::make_unique<BinaryExpressionNode>(std::move(node), term(), op);
    }

    return node;
}

std::unique_ptr<ExpressionNode> Parser::term() {
    // Parse factors and handle multiplication/division
    std::unique_ptr<ExpressionNode> node = factor();

    while (currentToken.type == TokenType::STAR || currentToken.type == TokenType::SLASH) {
        Token op = currentToken;
        consume();
        node = std::make_unique<BinaryExpressionNode>(std::move(node), term(), op);
    }

    return node;
}

std::unique_ptr<ExpressionNode> Parser::factor() {
    // Number literals
    if (currentToken.type == TokenType::NUMBER) {
        auto node = std::make_unique<NumberNode>(std::stod(
                std::string(currentToken.start, currentToken.start + currentToken.length)
        ));
        consume();
        return node;
    }
        // Parenthesized expressions
    else if (currentToken.type == TokenType::LEFT_PAREN) {
        consume();
        auto node = expression();
        match(TokenType::RIGHT_PAREN);
        return node;
    }

    error("Invalid factor");
    return nullptr; // This is just to satisfy the compiler; error() should throw an exception
}

void Parser::error(const std::string &message) {
    std::cerr << message << std::endl;
    throw std::runtime_error(message);
}

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

class ExpressionPrinter : public NodeVisitor {
public:
    void visit(BinaryExpressionNode* node) override {
        std::cout << "(";
        node->left->accept(this);
        std::cout << " " << getTokenTypeName(node->op.type) << " ";
        node->right->accept(this);
        std::cout << ")";
    }

    void visit(UnaryExpressionNode* node) override {
        std::cout << getTokenTypeName(node->op.type);
        node->expression->accept(this);
    }

    void visit(NumberNode* node) override {
        std::cout << node->value;
    }

    void visit(ProgramNode* node) override {
        std::cout << "ProgramNode";
    }

    void visit(ExpressionNode* node) override {
        std::cout << "ExpressionNode";
    }

    void visit(PrintNode* node) override {
        std::cout << "PrintNode";
        node->expression->accept(this);
    }
};

std::unique_ptr<StatementNode> Parser::statement() {
    if (currentToken.type == TokenType::PRINTLN) {
        consume();
        match(TokenType::LEFT_PAREN);
        auto expressionNode = expression();
        match(TokenType::RIGHT_PAREN);
        return std::make_unique<PrintNode>(std::move(expressionNode));
    }

    error("Invalid statement");
    return nullptr; // This is just to satisfy the compiler; error() should throw an exception
}

void Parser::parse() {
//    auto node = expression();
//    print_binary_expression_node(*dynamic_cast<BinaryExpressionNode *>(node.get()));
    ExpressionPrinter printer;
    IRGenerator irGenerator;
//    irGenerator.initializeContext();
//    node->accept(&printer);

    // TODO: Make the IR generator generate incrementally.
    //  And move the IR generator outside of this function.

    auto node = program();

//    std::cout << node->statements.size() << std::endl;

    for (auto &statement : node->statements) {
        statement->accept(&printer);
        statement->accept(&irGenerator);
        std::cout << std::endl;
    }

    irGenerator.logModule();

//    expression();
//    program();
}
