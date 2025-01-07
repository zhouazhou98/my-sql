#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "ast.h"
#include <vector>
#include <memory>

class Parser {
private:
    std::vector<Token> tokens;
    size_t pos = 0;

    const Token& current() const;
    const Token& advance();
    const Token& expect(TokenType type, const std::string& error_message);

public:
    explicit Parser(const std::vector<Token>& tokens);
    std::unique_ptr<ASTNode> parse();
    std::unique_ptr<ASTNode> parseSelect();
    std::unique_ptr<ASTNode> parseInsert();
    std::unique_ptr<ASTNode> parseUpdate();
    std::unique_ptr<ASTNode> parseWhere();
};

#endif // PARSER_H

