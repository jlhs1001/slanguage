//
// Created by Liam Seewald on 3/7/24.
//

#include "IRGenerator.h"
#include <iostream>

void IRGenerator::visit(ProgramNode *node) {
}

void IRGenerator::visit(PrintNode *node) {
    node->expression->accept(this);
}

void IRGenerator::visit(NumberNode *node) {
    lastValue = llvm::ConstantInt::get(*context, llvm::APInt(32, node->value));
}

void IRGenerator::visit(ExpressionNode *node) {
}

void IRGenerator::visit(BinaryExpressionNode *node) {
    node->left->accept(this);
    llvm::Value *left = lastValue;
    node->right->accept(this);
    llvm::Value *right = lastValue;

    switch (node->op.type) {
        case TokenType::PLUS:
            lastValue = builder->CreateAdd(left, right, "addtmp");
            break;
        case TokenType::MINUS:
            lastValue = builder->CreateSub(left, right, "subtmp");
            break;
        case TokenType::STAR:
            lastValue = builder->CreateMul(left, right, "multmp");
            break;
        case TokenType::SLASH:
            lastValue = builder->CreateSDiv(left, right, "divtmp");
            break;
        default:
            throw std::runtime_error("Invalid binary operator");
    }
}

void IRGenerator::visit(UnaryExpressionNode *node) {
}
//
//void IRGenerator::initializeContext() {
//
//}
