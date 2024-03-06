#include <iostream>
#include "lexer/Lexer.h"
#include "parser/Parser.h"



int main() {
    Lexer lexer("../tests/main.sl");
//    lexer.advance();

//    std::cout << *lexer.current << std::endl;

//    Token tk = lexer.getNextToken();
//    while (tk.type != TokenType::END_OF_FILE) {
//        std::cout << getTokenTypeName(tk.type) << std::endl;
//        tk = lexer.getNextToken();
//    }

    std::cout << lexer.source << std::endl;

    Parser parser(&lexer);
    parser.parse();

    return 0;
}