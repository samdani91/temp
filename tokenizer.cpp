#include <iostream>
#include <vector>
#include <regex>
#include "token.h"

std::vector<Token> tokenize(const std::string& sourceCode) {
    std::vector<Token> tokens;

    // Regular expressions for different token types.
    std::regex regexIdentifier(R"([a-zA-Z_][a-zA-Z0-9_]*)");
    std::regex regexIntLiteral(R"(\d+)");
    std::regex regexCharLiteral(R"('(.|\\[btnvfr'\\"0-7]{1,4})')");
    std::regex regexStringLiteral(R"("([^"\\\n]|\\.)*")");
    std::regex regexOperator(R"([+\-*/=])");
    std::regex regexSemicolon(R"(;)");
    std::regex regexLeftParenthesis(R"(\()");
    std::regex regexRightParenthesis(R"(\))");
    std::regex regexLeftBrace(R"(\{)");
    std::regex regexRightBrace(R"(\})");
    std::regex regexComma(R"(,)");

    // Regular expression pattern for skipping white spaces and comments.
    std::regex regexSkip(R"(\s+|//.*|/\*[\s\S]*?\*/)");

    // Tokenize the source code using regular expressions.
    int lineNumber = 1;
    int columnNumber = 1;
    std::smatch match;

    auto nextMatchPosition = [&](const std::string& source) {
        if (std::regex_search(source, match, regexSkip)) {
            int matchStart = match.position();
            int matchEnd = matchStart + match.length();

            // Update line and column numbers.
            int nextLineBreak = source.find_first_of("\n", matchStart);
            if (nextLineBreak != std::string::npos && nextLineBreak < matchEnd) {
                lineNumber++;
                columnNumber = matchEnd - nextLineBreak;
            } else {
                columnNumber += match.length();
            }

            return matchStart;
        }
        return static_cast<int>(source.size());
    };

    int position = nextMatchPosition(sourceCode);
    while (position < sourceCode.size()) {
        std::string remainingCode = sourceCode.substr(position);
        TokenType type = TokenType::IDENTIFIER; // Default to identifier type.
        std::string lexeme;

        // Determine the token type based on the regular expression.
        if (std::regex_search(remainingCode, match, regexIdentifier))
            type = TokenType::IDENTIFIER;
        else if (std::regex_search(remainingCode, match, regexIntLiteral))
            type = TokenType::INT_LITERAL;
        else if (std::regex_search(remainingCode, match, regexCharLiteral))
            type = TokenType::CHAR_LITERAL;
        else if (std::regex_search(remainingCode, match, regexStringLiteral))
            type = TokenType::STRING_LITERAL;
        else if (std::regex_search(remainingCode, match, regexOperator))
            type = TokenType::OPERATOR;
        else if (std::regex_search(remainingCode, match, regexSemicolon))
            type = TokenType::SEMICOLON;
        else if (std::regex_search(remainingCode, match, regexLeftParenthesis))
            type = TokenType::LEFT_PARENTHESIS;
        else if (std::regex_search(remainingCode, match, regexRightParenthesis))
            type = TokenType::RIGHT_PARENTHESIS;
        else if (std::regex_search(remainingCode, match, regexLeftBrace))
            type = TokenType::LEFT_BRACE;
        else if (std::regex_search(remainingCode, match, regexRightBrace))
            type = TokenType::RIGHT_BRACE;
        else if (std::regex_search(remainingCode, match, regexComma))
            type = TokenType::COMMA;

        lexeme = match.str();

        // Add the token to the vector.
        tokens.push_back({type, lexeme, lineNumber, columnNumber});

        position = nextMatchPosition(remainingCode);
    }

    return tokens;
}
