//
// Created by Liam Seewald on 3/6/24.
//

#include "UnaryExpressionNode.h"

void UnaryExpressionNode::accept(NodeVisitor *visitor) {
    visitor->visit(this);
}