#ifndef __ZHOU_SQL_LEXER_H__
#define __ZHOU_SQL_LEXER_H__

#include "token.h"
#include <string>
#include <vector>

class Lexer {

public:
    explicit Lexer(const std::string & input);
    std::vector<Token> tokenize();

private:
    char peek() const;
    char advance();

    std::string input;
    size_t pos = 0;
    int column = 0;
    int line = 1;

};

#endif // ! __ZHOU_SQL_LEXER_H__
