//
// Created by Liam Seewald on 3/7/24.
//

#ifndef SLANG_PRINTNODE_H
#define SLANG_PRINTNODE_H

#include <memory>

#include "NodeVisitor.h"
#include "expression/ExpressionNode.h"
#include "StatementNode.h"

class PrintNode : public StatementNode {
public:
    std::unique_ptr<ExpressionNode> expression;
public:
    PrintNode(std::unique_ptr<ExpressionNode> expression) : expression(std::move(expression)) {}

    ~PrintNode() override = default;

    void accept(class NodeVisitor *visitor) override;
};


#endif //SLANG_PRINTNODE_H
