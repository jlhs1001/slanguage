//
// Created by Liam Seewald on 3/6/24.
//

#include "BinaryExpressionNode.h"

void BinaryExpressionNode::accept(struct NodeVisitor *visitor) {
    visitor->visit(this);
}
