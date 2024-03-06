//
// Created by Liam Seewald on 3/6/24.
//

#ifndef SLANG_BINARYEXPRESSIONNODE_H
#define SLANG_BINARYEXPRESSIONNODE_H

#include <utility>
#include <memory>
#include "ExpressionNode.h"
#include "Token.h"
#include "NodeVisitor.h"

class BinaryExpressionNode : public ExpressionNode {
public:
    std::unique_ptr<ExpressionNode> left;
    std::unique_ptr<ExpressionNode> right;
    Token op;

    BinaryExpressionNode(std::unique_ptr<ExpressionNode> left, std::unique_ptr<ExpressionNode> right, Token op)
            : left(std::move(left)),
              right(std::move(right)),
              op(op) {}

    void accept(class NodeVisitor* visitor) override;
};


#endif //SLANG_BINARYEXPRESSIONNODE_H
