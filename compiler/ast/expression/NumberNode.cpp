//
// Created by Liam Seewald on 3/6/24.
//

#include "NumberNode.h"

void NumberNode::accept(NodeVisitor *visitor) {
    visitor->visit(this);
}
