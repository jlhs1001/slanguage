//
// Created by Liam Seewald on 3/7/24.
//

#include "PrintNode.h"

void PrintNode::accept(struct NodeVisitor *visitor) {
    visitor->visit(this);
}
