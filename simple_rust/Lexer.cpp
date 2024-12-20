#include "Lexer.h"
#include <iostream>
#include <cctype>

Lexer::Lexer(const std::string& source) : source(source), index(0) {}

Token Lexer::nextToken() {
    while (index < source.size() && std::isspace(source[index])) {
        index++;
    }

    if (index == source.size()) {
        return Token{TokenType::TOKEN_EOF, ""};
    }

    char currentChar = source[index];

    // Handle keywords and identifiers
    if (std::isalpha(currentChar)) {
        std::string value;
        while (index < source.size() && std::isalnum(source[index])) {
            value += source[index++];
        }
        if (value == "fn") return Token{TokenType::FUNCTION, value};
        if (value == "let") return Token{TokenType::LET, value};
        if (value == "return") return Token{TokenType::RETURN, value};
        return Token{TokenType::IDENTIFIER, value};
    }

    // Handle numbers
    if (std::isdigit(currentChar)) {
        std::string value;
        while (index < source.size() && std::isdigit(source[index])) {
            value += source[index++];
        }
        return Token{TokenType::NUMBER, value};
    }

    // Handle symbols
    switch (currentChar) {
        case '(': index++; return Token{TokenType::LPAREN, "("};
        case ')': index++; return Token{TokenType::RPAREN, ")"};
        case '{': index++; return Token{TokenType::LBRACE, "{"};
        case '}': index++; return Token{TokenType::RBRACE, "}"};
        case ',': index++; return Token{TokenType::COMMA, ","};
        case ':': index++; return Token{TokenType::COLON, ":"};
        case '-':
            if (source[index + 1] == '>') {
                index += 2;
                return Token{TokenType::ARROW, "->"};
            }
        break;
        case '+': index++; return Token{TokenType::PLUS, "+"};
        default: ;
    }

    return Token{TokenType::INVALID, std::string(1, currentChar)};
}
