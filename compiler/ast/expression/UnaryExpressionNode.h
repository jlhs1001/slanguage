//
// Created by Liam Seewald on 3/6/24.
//

#ifndef SLANG_UNARYEXPRESSIONNODE_H
#define SLANG_UNARYEXPRESSIONNODE_H

#include "ExpressionNode.h"
#include "NodeVisitor.h"
#include "Token.h"

class UnaryExpressionNode : public ExpressionNode {
public:
    ExpressionNode* expression;
    Token op;

    UnaryExpressionNode(ExpressionNode* expression, Token op) : expression(expression), op(op) {}

    void accept(NodeVisitor* visitor) override;
};


#endif //SLANG_UNARYEXPRESSIONNODE_H
