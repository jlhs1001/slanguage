//
// Created by Liam Seewald on 3/6/24.
//

#ifndef SLANG_STATEMENTNODE_H
#define SLANG_STATEMENTNODE_H


class StatementNode {
public:
    virtual ~StatementNode() = default;
    virtual void accept(class NodeVisitor* visitor) = 0;
};


#endif //SLANG_STATEMENTNODE_H
