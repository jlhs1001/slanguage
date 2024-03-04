cmake_minimum_required(VERSION 3.26)
project(slang)

set(CMAKE_CXX_STANDARD 17)

add_executable(slang compiler/main.cpp
        compiler/Lexer.h
        compiler/Lexer.cpp)
