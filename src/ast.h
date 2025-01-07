#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>

// 抽象语法树的基类
class ASTNode {
public:
    virtual ~ASTNode() = default;
};

// 表达式节点
class ExpressionNode : public ASTNode {
public:
    std::string value;
    ExpressionNode(const std::string& value) : value(value) {}
};

// SELECT 语句节点
class SelectNode : public ASTNode {
public:
    std::vector<std::string> columns;  // 查询列
    std::string table;                 // 查询表
    std::unique_ptr<ASTNode> where;    // WHERE 条件
};

// INSERT 语句节点
class InsertNode : public ASTNode {
public:
    std::string table;                 // 插入表
    std::vector<std::string> columns;  // 插入列
    std::vector<std::string> values;   // 插入值
};

// UPDATE 语句节点
class UpdateNode : public ASTNode {
public:
    std::string table;                 // 更新表
    std::string column;                // 更新列
    std::string value;                 // 更新值
    std::unique_ptr<ASTNode> where;    // WHERE 条件
};

// WHERE 条件节点
class WhereNode : public ASTNode {
public:
    std::string column;                // 条件列
    std::string op;                    // 操作符
    std::string value;                 // 条件值
};

#endif // AST_H

