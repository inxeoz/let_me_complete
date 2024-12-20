#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

// Token types
enum class TokenType {
    FUNCTION,    // 'fn'
    LET,         // 'let'
    RETURN,      // 'return'
    IDENTIFIER,  // Function or variable name
    NUMBER,      // Integer literals
    LPAREN,      // '('
    RPAREN,      // ')'
    LBRACE,      // '{'
    RBRACE,      // '}'
    COMMA,       // ','
    COLON,       // ':'
    ARROW,       // '->'
    PLUS,        // '+'
    TOKEN_EOF,   // End of file (renamed to avoid conflict with standard EOF)
    INVALID      // Invalid token
};

// Token structure
struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    explicit Lexer(const std::string& source);
    Token nextToken();

private:
    std::string source;
    size_t index;
};

#endif // LEXER_H
