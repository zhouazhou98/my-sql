#include "parser.h"
#include <stdexcept>

// 获取当前 Token
const Token& Parser::current() const {
    return tokens[pos];
}

// 消耗当前 Token，返回其值
const Token& Parser::advance() {
    return tokens[pos++];
}

// 检查当前 Token 类型并消耗，否则抛出错误
const Token& Parser::expect(TokenType type, const std::string& error_message) {
    if (current().m_type == type) {
        return advance();
    }
    throw std::runtime_error(error_message);
}

// 构造 Parser
Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

// 主解析入口
std::unique_ptr<ASTNode> Parser::parse() {
    if (current().m_type == TokenType::SELECT) {
        return parseSelect();
    } else if (current().m_type == TokenType::INSERT) {
        return parseInsert();
    } else if (current().m_type == TokenType::UPDATE) {
        return parseUpdate();
    }
    throw std::runtime_error("Unsupported SQL command: " + current().m_value);
}

// 解析 SELECT 语句
std::unique_ptr<ASTNode> Parser::parseSelect() {
    advance();  // 消耗 SELECT

    // 解析列名
    std::vector<std::string> columns;
    while (current().m_type != TokenType::FROM) {
        if (current().m_type == TokenType::COMMA) {
            advance();  // 跳过逗号
        } else {
            columns.push_back(expect(TokenType::IDENTIFIER, "Expected column name").m_value);
        }
    }

    // 消耗 FROM
    expect(TokenType::FROM, "Expected 'FROM' keyword");

    // 解析表名
    std::string table = expect(TokenType::IDENTIFIER, "Expected table name").m_value;

    // 解析 WHERE 条件（如果存在）
    std::unique_ptr<ASTNode> where = nullptr;
    if (current().m_type == TokenType::WHERE) {
        advance();  // 消耗 WHERE
        where = parseWhere();
    }

    auto node = std::make_unique<SelectNode>();
    node->columns = columns;
    node->table = table;
    node->where = std::move(where);
    return node;
}

// 解析 INSERT 语句
std::unique_ptr<ASTNode> Parser::parseInsert() {
    advance();  // 消耗 INSERT
    expect(TokenType::INTO, "Expected 'INTO' keyword");

    // 表名
    std::string table = expect(TokenType::IDENTIFIER, "Expected table name").m_value;

    // 列名
    expect(TokenType::PAREN_OPEN, "Expected '(' after table name");
    std::vector<std::string> columns;
    while (current().m_type != TokenType::PAREN_CLOSE) {
        if (current().m_type == TokenType::COMMA) {
            advance();
        } else {
            columns.push_back(expect(TokenType::IDENTIFIER, "Expected column name").m_value);
        }
    }
    expect(TokenType::PAREN_CLOSE, "Expected ')' after column list");

    // VALUES 关键字
    expect(TokenType::VALUES, "Expected 'VALUES' keyword");

    // 插入值
    expect(TokenType::PAREN_OPEN, "Expected '(' after VALUES");
    std::vector<std::string> values;
    while (current().m_type != TokenType::PAREN_CLOSE) {
        if (current().m_type == TokenType::COMMA) {
            advance();
        } else if (current().m_type == TokenType::NUMBER || current().m_type == TokenType::STRING) {
            values.push_back(advance().m_value);  // 支持数字和字符串
        } else {
            throw std::runtime_error("Expected value");
        }
    }
    expect(TokenType::PAREN_CLOSE, "Expected ')' after values list");

    auto node = std::make_unique<InsertNode>();
    node->table = table;
    node->columns = columns;
    node->values = values;
    return node;
}


// 解析 UPDATE 语句
std::unique_ptr<ASTNode> Parser::parseUpdate() {
    advance();  // 消耗 UPDATE

    // 表名
    std::string table = expect(TokenType::IDENTIFIER, "Expected table name").m_value;

    // SET 关键字
    expect(TokenType::SET, "Expected 'SET' keyword");

    // 更新列和值
    std::string column = expect(TokenType::IDENTIFIER, "Expected column name").m_value;
    expect(TokenType::OPERATOR, "Expected '='");

    std::string value;
    if (current().m_type == TokenType::NUMBER || current().m_type == TokenType::STRING) {
        value = advance().m_value;  // 支持数字和字符串
    } else {
        throw std::runtime_error("Expected value");
    }

    // WHERE 条件
    std::unique_ptr<ASTNode> where = nullptr;
    if (current().m_type == TokenType::WHERE) {
        advance();
        where = parseWhere();
    }

    auto node = std::make_unique<UpdateNode>();
    node->table = table;
    node->column = column;
    node->value = value;
    node->where = std::move(where);
    return node;
}


// 解析 WHERE 条件
std::unique_ptr<ASTNode> Parser::parseWhere() {
    std::string column = expect(TokenType::IDENTIFIER, "Expected column name").m_value;
    std::string op = expect(TokenType::OPERATOR, "Expected operator").m_value;
    std::string value = expect(TokenType::NUMBER, "Expected value").m_value;

    auto node = std::make_unique<WhereNode>();
    node->column = column;
    node->op = op;
    node->value = value;
    return node;
}

