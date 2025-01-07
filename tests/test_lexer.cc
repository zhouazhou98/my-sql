#include <iostream>
#include <vector>
#include <string>
#include "lexer.h"

void printToken(const Token& token) {
    std::cout << "Token(Type: " << static_cast<int>(token.m_type) 
              << ", Value: \"" << token.m_value 
              << "\", Line: " << token.m_line 
              << ", Column: " << token.m_column << ")\n";
}

void testTokenizeSelectStatement() {
    std::string input = "SELECT name, age FROM users WHERE age > 18;";
    Lexer lexer(input);
    auto tokens = lexer.tokenize();

    std::cout << "Test: Tokenize SELECT statement\n";
    for (const auto& token : tokens) {
        printToken(token);
    }
    std::cout << "\n";
}

void testTokenizeInsertStatement() {
    std::string input = "INSERT INTO users (id, name) VALUES (1, 'Alice');";
    Lexer lexer(input);
    auto tokens = lexer.tokenize();

    std::cout << "Test: Tokenize INSERT statement\n";
    for (const auto& token : tokens) {
        printToken(token);
    }
    std::cout << "\n";
}

void testTokenizeUpdateStatement() {
    std::string input = "UPDATE users SET age = age + 1 WHERE id = 10;";
    Lexer lexer(input);
    auto tokens = lexer.tokenize();

    std::cout << "Test: Tokenize UPDATE statement\n";
    for (const auto& token : tokens) {
        printToken(token);
    }
    std::cout << "\n";
}

void testTokenizeTransactionBlock() {
    std::string input = R"(
        BEGIN TRANSACTION;
        INSERT INTO accounts (id, balance) VALUES (1, 100);
        UPDATE accounts SET balance = balance - 50 WHERE id = 1;
        COMMIT;
    )";
    Lexer lexer(input);
    auto tokens = lexer.tokenize();

    std::cout << "Test: Tokenize Transaction Block\n";
    for (const auto& token : tokens) {
        printToken(token);
    }
    std::cout << "\n";
}

void testTokenizeInvalidInput() {
    std::string input = "INVALID_KEYWORD;";
    Lexer lexer(input);
    auto tokens = lexer.tokenize();

    std::cout << "Test: Tokenize Invalid Input\n";
    for (const auto& token : tokens) {
        printToken(token);
    }
    std::cout << "\n";
}

int main() {
    // Run tests
    testTokenizeSelectStatement();
    testTokenizeInsertStatement();
    testTokenizeUpdateStatement();
    testTokenizeTransactionBlock();
    testTokenizeInvalidInput();

    return 0;
}

