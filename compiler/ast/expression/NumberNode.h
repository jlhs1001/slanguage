//
// Created by Liam Seewald on 3/6/24.
//

#ifndef SLANG_NUMBERNODE_H
#define SLANG_NUMBERNODE_H


#include "ExpressionNode.h"
#include "NodeVisitor.h"

class NumberNode : public ExpressionNode {
public:
    int value;

    NumberNode(int value) : value(value) {}

    int getValue() {
        return value;
    }

    void accept(NodeVisitor* visitor) override;
};


#endif //SLANG_NUMBERNODE_H
