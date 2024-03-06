//
// Created by Liam Seewald on 3/6/24.
//

#ifndef SLANG_EXPRESSIONNODE_H
#define SLANG_EXPRESSIONNODE_H


class ExpressionNode {
public:
    virtual ~ExpressionNode() = default;
    virtual void accept(class NodeVisitor* visitor) = 0;
};


#endif //SLANG_EXPRESSIONNODE_H
