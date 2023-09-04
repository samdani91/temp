#include <iostream>
#include "token.h"
#include "tokenizer.cpp"

int main() {
    // Read the C source code from the file or take input from the user.
    std::string sourceCode = R"(
        int main() {
            int x = 10;
            printf("Hello, World!");
            return 0;
        }
    )";

    // Tokenize the code.
    std::vector<Token> tokens = tokenize(sourceCode);

    // Print the tokens.
    for (const Token& token : tokens) {
        std::cout << "Type: " << static_cast<int>(token.type) << " | Lexeme: " << token.lexeme;
        std::cout << " | Line: " << token.line << " | Column: " << token.column << std::endl;
    }

    return 0;
}
