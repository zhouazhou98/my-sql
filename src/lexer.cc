#include "lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& input) : input(input) {}

char Lexer::peek() const {
    return pos < input.size() ? input[pos] : '\0';
}

char Lexer::advance() {
    if (pos < input.size()) {
        char c = input[pos++];
        column++;
        if (c == '\n') {
            line++;
            column = 0;
        }
        return c;
    }
    return '\0';
}


std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (peek() != '\0') {
        char c = peek();

        // 跳过空白字符
        if (std::isspace(c)) {
            advance();
            continue;
        }

        size_t token_start_column = column;

        // 处理标识符和关键字
        if (std::isalpha(c)) {
            std::string word;
            while (std::isalnum(peek()) || peek() == '_') word += advance();

            // 检查是否是 SQL 关键字
            if (word == "SELECT") tokens.emplace_back(TokenType::SELECT, word, line, token_start_column);
            else if (word == "INSERT") tokens.emplace_back(TokenType::INSERT, word, line, token_start_column);
            else if (word == "UPDATE") tokens.emplace_back(TokenType::UPDATE, word, line, token_start_column);
            else if (word == "DELETE") tokens.emplace_back(TokenType::DELETE, word, line, token_start_column);
            else if (word == "SET") tokens.emplace_back(TokenType::SET, word, line, token_start_column);
            else if (word == "FROM") tokens.emplace_back(TokenType::FROM, word, line, token_start_column);
            else if (word == "WHERE") tokens.emplace_back(TokenType::WHERE, word, line, token_start_column);
            else if (word == "JOIN") tokens.emplace_back(TokenType::JOIN, word, line, token_start_column);
            else if (word == "INNER") tokens.emplace_back(TokenType::INNER, word, line, token_start_column);
            else if (word == "LEFT") tokens.emplace_back(TokenType::LEFT, word, line, token_start_column);
            else if (word == "RIGHT") tokens.emplace_back(TokenType::RIGHT, word, line, token_start_column);
            else if (word == "FULL") tokens.emplace_back(TokenType::FULL, word, line, token_start_column);
            else if (word == "ON") tokens.emplace_back(TokenType::ON, word, line, token_start_column);
            else if (word == "VALUES") tokens.emplace_back(TokenType::VALUES, word, line, token_start_column);
            else if (word == "INTO") tokens.emplace_back(TokenType::INTO, word, line, token_start_column);
            else if (word == "BEGIN") tokens.emplace_back(TokenType::BEGIN, word, line, token_start_column);
            else if (word == "TRANSACTION") tokens.emplace_back(TokenType::TRANSACTION, word, line, token_start_column);
            else if (word == "COMMIT") tokens.emplace_back(TokenType::COMMIT, word, line, token_start_column);
            else if (word == "ROLLBACK") tokens.emplace_back(TokenType::ROLLBACK, word, line, token_start_column);
            else tokens.emplace_back(TokenType::IDENTIFIER, word, line, token_start_column);
        }

        // 处理数字
        else if (std::isdigit(c)) {
            std::string number;
            while (std::isdigit(peek())) number += advance();
            tokens.emplace_back(TokenType::NUMBER, number, line, token_start_column);
        }

        // 处理字符串
        else if (c == '\'' || c == '\"') {
            char quote = advance();  // 获取引号字符
            std::string str;
            while (peek() != quote && peek() != '\0') str += advance();
            if (peek() == quote) advance();  // 跳过闭合引号
            tokens.emplace_back(TokenType::STRING, str, line, token_start_column);
        }

        // 处理运算符和分隔符
        else if (c == ',') {
            tokens.emplace_back(TokenType::COMMA, std::string(1, c), line, token_start_column);
            advance();
        } else if (c == ';') {
            tokens.emplace_back(TokenType::SEMICOLON, std::string(1, c), line, token_start_column);
            advance();
        } else if (c == '(') {
            tokens.emplace_back(TokenType::PAREN_OPEN, std::string(1, c), line, token_start_column);
            advance();
        } else if (c == ')') {
            tokens.emplace_back(TokenType::PAREN_CLOSE, std::string(1, c), line, token_start_column);
            advance();
        } else if (c == '=') {
            tokens.emplace_back(TokenType::OPERATOR, "=", line, token_start_column);
            advance();
        } else if (c == '<' || c == '>') {
            std::string op(1, advance());
            if (peek() == '=') op += advance();  // 支持 <= 和 >=
            tokens.emplace_back(TokenType::OPERATOR, op, line, token_start_column);
        } else if (c == '!') {
            std::string op(1, advance());
            if (peek() == '=') op += advance();  // 支持 !=
            tokens.emplace_back(TokenType::OPERATOR, op, line, token_start_column);
        } else {
            // 未知字符
            tokens.emplace_back(TokenType::OPERATOR, std::string(1, c), line, token_start_column);
            advance();
        }
    }

    // 添加结束标记
    tokens.emplace_back(TokenType::END_OF_FILE, "", line, column);
    return tokens;
}
