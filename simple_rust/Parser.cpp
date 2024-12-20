#include "Parser.h"
#include <iostream>

Parser::Parser(Lexer& lexer) : lexer(lexer) {}

std::unique_ptr<ASTNode> Parser::parseFunction() {
    // Match function declaration `fn`
    Token token = lexer.nextToken();
    if (token.type != TokenType::FUNCTION) {
        std::cerr << "Expected 'fn'\n";
        return nullptr;
    }

    // Parse function name
    token = lexer.nextToken();
    if (token.type != TokenType::IDENTIFIER) {
        std::cerr << "Expected function name\n";
        return nullptr;
    }
    std::string funcName = token.value;

    // Parse parameters
    std::vector<std::pair<std::string, std::string>> parameters;
    token = lexer.nextToken();
    if (token.type == TokenType::LPAREN) {
        token = lexer.nextToken();
        while (token.type == TokenType::IDENTIFIER) {
            std::string paramName = token.value;
            token = lexer.nextToken();
            if (token.type != TokenType::COLON) {
                std::cerr << "Expected ':' after parameter name\n";
                return nullptr;
            }
            token = lexer.nextToken();
            if (token.type != TokenType::IDENTIFIER) {
                std::cerr << "Expected type after ':'\n";
                return nullptr;
            }
            parameters.push_back({paramName, token.value});
            token = lexer.nextToken();
            if (token.type == TokenType::COMMA) {
                token = lexer.nextToken();
            }
        }
        if (token.type != TokenType::RPAREN) {
            std::cerr << "Expected ')'\n";
            return nullptr;
        }
    }

    // Parse return type
    token = lexer.nextToken();
    if (token.type != TokenType::ARROW) {
        std::cerr << "Expected '->'\n";
        return nullptr;
    }

    token = lexer.nextToken();
    if (token.type != TokenType::IDENTIFIER) {
        std::cerr << "Expected return type\n";
        return nullptr;
    }
    std::string returnType = token.value;

    return std::make_unique<FunctionNode>(funcName, parameters, returnType);
}
