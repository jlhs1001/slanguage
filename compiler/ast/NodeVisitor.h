//
// Created by Liam Seewald on 3/6/24.
//

#ifndef SLANG_NODEVISITOR_H
#define SLANG_NODEVISITOR_H

class ExpressionNode;
class NumberNode;
class BinaryExpressionNode;
class UnaryExpressionNode;
class ProgramNode;

class NodeVisitor {
public:
    virtual void visit(ExpressionNode* node) = 0;
    virtual void visit(NumberNode* node) = 0;
    virtual void visit(BinaryExpressionNode* node) = 0;
    virtual void visit(UnaryExpressionNode* node) = 0;
    virtual void visit(ProgramNode* node) = 0;
};


#endif //SLANG_NODEVISITOR_H
