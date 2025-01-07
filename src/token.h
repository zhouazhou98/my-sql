#ifndef __ZHOU_SQL_TOKEN_H__
#define __ZHOU_SQL_TOKEN_H__

#include <string>
#include <variant>

enum class TokenType {
    SELECT,
    INSERT,
    UPDATE,
    DELETE,
    SET,
    BEGIN,
    TRANSACTION,
    COMMIT,
    ROLLBACK,
    FROM,
    WHERE,
    JOIN,
    INNER,
    LEFT,
    RIGHT,
    FULL,
    ON,
    VALUES,
    INTO,
    IDENTIFIER,
    NUMBER,
    STRING,
    OPERATOR,
    COMMA,
    SEMICOLON,
    PAREN_OPEN,
    PAREN_CLOSE,
    END_OF_FILE,
};

struct Token {
    TokenType m_type;
    std::string m_value;
    int m_line;
    int m_column;

    Token(TokenType type, const std::string & value, int line, int column)
        : m_type(type), m_value(value),  m_line(line), m_column(column) {}
};

#endif // ! __ZHOU_SQL_TOKEN_H__
