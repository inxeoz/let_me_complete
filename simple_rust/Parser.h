#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include <memory>
#include <vector>

// Forward declaration
class ASTNode;

class Parser {
public:
    Parser(Lexer& lexer);
    std::unique_ptr<ASTNode> parseFunction();

private:
    Lexer& lexer;
};

// AST Node structure (for functions and expressions)
class ASTNode {
public:
    virtual ~ASTNode() = default;
};

class FunctionNode : public ASTNode {
public:
    FunctionNode(const std::string& name, const std::vector<std::pair<std::string, std::string>>& params, const std::string& returnType)
        : name(name), params(params), returnType(returnType) {}

    std::string name;
    std::vector<std::pair<std::string, std::string>> params;
    std::string returnType;
};

#endif // PARSER_H
