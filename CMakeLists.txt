cmake_minimum_required(VERSION 3.26)
project(slang)

set(CMAKE_CXX_STANDARD 17)

include_directories(compiler/Lexer)

add_executable(slang compiler/main.cpp
        compiler/Lexer/Lexer.h
        compiler/Lexer/Lexer.cpp
        compiler/lexer/Utils.h
        compiler/lexer/Utils.cpp
        compiler/lexer/Token.h)
