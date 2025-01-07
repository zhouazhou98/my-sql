#include <iostream>
#include <memory>
#include <vector>
#include "lexer.h"
#include "parser.h"
#include "ast.h"

// 辅助函数：打印 SelectNode AST
void printSelectNode(const SelectNode* node) {
    std::cout << "SelectNode:\n";
    std::cout << "  Columns: ";
    for (const auto& column : node->columns) {
        std::cout << column << " ";
    }
    std::cout << "\n  Table: " << node->table << "\n";

    if (node->where) {
        const auto* where = dynamic_cast<WhereNode*>(node->where.get());
        if (where) {
            std::cout << "  Where:\n";
            std::cout << "    Column: " << where->column << "\n";
            std::cout << "    Operator: " << where->op << "\n";
            std::cout << "    Value: " << where->value << "\n";
        }
    }
    std::cout << "\n";
}

// 辅助函数：打印 InsertNode AST
void printInsertNode(const InsertNode* node) {
    std::cout << "InsertNode:\n";
    std::cout << "  Table: " << node->table << "\n  Columns: ";
    for (const auto& column : node->columns) {
        std::cout << column << " ";
    }
    std::cout << "\n  Values: ";
    for (const auto& value : node->values) {
        std::cout << value << " ";
    }
    std::cout << "\n";
}

// 辅助函数：打印 UpdateNode AST
void printUpdateNode(const UpdateNode* node) {
    std::cout << "UpdateNode:\n";
    std::cout << "  Table: " << node->table << "\n";
    std::cout << "  Column: " << node->column << "\n";
    std::cout << "  Value: " << node->value << "\n";

    if (node->where) {
        const auto* where = dynamic_cast<WhereNode*>(node->where.get());
        if (where) {
            std::cout << "  Where:\n";
            std::cout << "    Column: " << where->column << "\n";
            std::cout << "    Operator: " << where->op << "\n";
            std::cout << "    Value: " << where->value << "\n";
        }
    }
    std::cout << "\n";
}

// 测试 SELECT 语句
void testSelectParser() {
    std::string input = "SELECT name, age FROM users WHERE age > 18;";
    Lexer lexer(input);
    Parser parser(lexer.tokenize());
    auto ast = parser.parse();

    std::cout << "Test: SELECT Parser\n";
    const auto* selectNode = dynamic_cast<SelectNode*>(ast.get());
    if (selectNode) {
        printSelectNode(selectNode);
    } else {
        std::cout << "Error: Failed to parse SELECT statement.\n";
    }
    std::cout << "\n";
}

// 测试 INSERT 语句
void testInsertParser() {
    std::string input = "INSERT INTO users (id, name) VALUES (1, 'Alice');";
    Lexer lexer(input);
    Parser parser(lexer.tokenize());
    auto ast = parser.parse();

    std::cout << "Test: INSERT Parser\n";
    const auto* insertNode = dynamic_cast<InsertNode*>(ast.get());
    if (insertNode) {
        printInsertNode(insertNode);
    } else {
        std::cout << "Error: Failed to parse INSERT statement.\n";
    }
    std::cout << "\n";
}

// 测试 UPDATE 语句
void testUpdateParser() {
    std::string input = "UPDATE users SET age = '30' WHERE id = 1;";
    Lexer lexer(input);
    Parser parser(lexer.tokenize());
    auto ast = parser.parse();

    std::cout << "Test: UPDATE Parser\n";
    const auto* updateNode = dynamic_cast<UpdateNode*>(ast.get());
    if (updateNode) {
        printUpdateNode(updateNode);
    } else {
        std::cout << "Error: Failed to parse UPDATE statement.\n";
    }
    std::cout << "\n";
}

int main() {
    // 运行测试
    testSelectParser();
    testInsertParser();
    testUpdateParser();

    return 0;
}

