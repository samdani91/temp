#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    // Add token types for keywords, identifiers, literals, operators, etc.
    IDENTIFIER,          // Example: variable names
    INT_LITERAL,         // Example: 123
    CHAR_LITERAL,        // Example: 'a'
    STRING_LITERAL,      // Example: "Hello, World!"
    PLUS,                // Example: +
    MINUS,               // Example: -
    ASTERISK,            // Example: *
    SLASH,               // Example: /
    ASSIGN,              // Example: =
    SEMICOLON,           // Example: ;
    LEFT_PARENTHESIS,    // Example: (
    RIGHT_PARENTHESIS,   // Example: )
    LEFT_BRACE,          // Example: {
    RIGHT_BRACE,         // Example: }
    COMMA,               // Example: ,
    OPERATOR,
    // Add more token types as needed.
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;   // Line number where the token was found (optional, for error reporting).
    int column; // Column number where the token was found (optional, for error reporting).
};

#endif // TOKEN_H