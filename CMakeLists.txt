cmake_minimum_required(VERSION 3.26)
project(slang)

set(CMAKE_CXX_STANDARD 17)

include_directories(compiler/lexer)
include_directories(compiler/ast)
include_directories(compiler/parser)

add_executable(slang compiler/main.cpp
        compiler/Lexer/Lexer.h
        compiler/Lexer/Lexer.cpp
        compiler/lexer/Utils.h
        compiler/lexer/Utils.cpp
        compiler/lexer/Token.h
        compiler/ast/ProgramNode.h
        compiler/ast/ProgramNode.cpp
        compiler/ast/expression/ExpressionNode.h
        compiler/ast/expression/ExpressionNode.cpp
        compiler/ast/expression/NumberNode.h
        compiler/ast/expression/NumberNode.cpp
        compiler/parser/Parser.h
        compiler/parser/Parser.cpp
        compiler/ast/expression/BinaryExpressionNode.h
        compiler/ast/expression/BinaryExpressionNode.cpp
        compiler/ast/NodeVisitor.h
        compiler/ast/NodeVisitor.cpp
        compiler/ast/expression/UnaryExpressionNode.h
        compiler/ast/expression/UnaryExpressionNode.cpp)
