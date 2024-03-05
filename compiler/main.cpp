#include <iostream>
#include "lexer/lexer.h"

int main() {
    Lexer lexer("../tests/main.sl");
    lexer.advance();

//    std::cout << *lexer.current << std::endl;

    std::cout << lexer.source << std::endl;
}