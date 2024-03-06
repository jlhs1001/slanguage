//
// Created by Liam Seewald on 3/6/24.
//

#ifndef SLANG_STATEMENTNODE_H
#define SLANG_STATEMENTNODE_H


class StatementNode {
public:
    virtual void codegen() = 0;
    virtual void print() = 0;
    virtual ~StatementNode() = default;

    StatementNode() = default;
};


#endif //SLANG_STATEMENTNODE_H
