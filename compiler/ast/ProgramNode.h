//
// Created by Liam Seewald on 3/6/24.
//

#ifndef SLANG_PROGRAMNODE_H
#define SLANG_PROGRAMNODE_H

#include <vector>
#include "statement/StatementNode.h"

class ProgramNode {
public:
    std::vector<std::unique_ptr<StatementNode>> statements;

//    virtual ~ProgramNode() {
//        for (auto &statement: statements) {
//            delete statement;
//        }
//    }

public:
    ProgramNode(std::vector<std::unique_ptr<StatementNode>> statements) : statements(std::move(statements)) {}
};


#endif //SLANG_PROGRAMNODE_H
