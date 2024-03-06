//
// Created by Liam Seewald on 3/6/24.
//

#ifndef SLANG_PROGRAMNODE_H
#define SLANG_PROGRAMNODE_H

#include <vector>
#include "statement/StatementNode.h"

class ProgramNode {
public:
    std::vector<StatementNode *> statements;

    void codegen() {
        for (auto &statement : statements) {
            statement->codegen();
        }
    }

    void print() {
        for (auto &statement : statements) {
            statement->print();
        }
    }

    virtual ~ProgramNode() {
        for (auto &statement : statements) {
            delete statement;
        }
    }
public:
    ProgramNode(std::vector<StatementNode *> statements) : statements(statements) {}
};


#endif //SLANG_PROGRAMNODE_H
