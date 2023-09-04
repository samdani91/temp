#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

// Function to explain each line of C code using regular expressions
void explainCode(const std::vector<std::string>& codeLines) {
    std::vector<std::pair<std::regex, std::string>> explanations = {
        {std::regex("#include\\s*<(.+?)>"), "includes the header file: $1"},
        {std::regex("int\\s+main\\s*\\(\\s*\\)"), "defines the main function"},
        {std::regex("\\{"), "opens a block"},
        {std::regex("\\}"), "closes a block"},
        {std::regex("return\\s+\\d+;?"), "returns an integer value"}
        // Add more regular expressions for other patterns and their explanations
    };

    for (size_t i = 0; i < codeLines.size(); ++i) {
        std::cout << "line " << i + 1 << " ";
        std::string line = codeLines[i];

        // Remove leading and trailing spaces from the line
        size_t start = line.find_first_not_of(" \t");
        size_t end = line.find_last_not_of(" \t");
        if (start != std::string::npos && end != std::string::npos)
            line = line.substr(start, end - start + 1);

        if (line.empty()) {
            std::cout << "is empty" << std::endl;
            continue;
        }

        // Check if it's a comment
        if (line[0] == '/' && line[1] == '/')
            std::cout << "has a single-line comment: " << line.substr(2) << std::endl;
        else {
            bool explained = false;
            for (const auto& exp : explanations) {
                if (std::regex_search(line, exp.first)) {
                    std::string explanation = std::regex_replace(line, exp.first, exp.second);
                    std::cout << "has " << explanation << std::endl;
                    explained = true;
                    break;
                }
            }
            if (!explained)
                std::cout << "has code: " << line << std::endl;
        }
    }
}

int main() {
    // Input file name
    std::string filename = "test.c";

    // Read the C source code from the file
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::vector<std::string> code;
    std::string line;
    while (std::getline(inputFile, line)) {
        code.push_back(line);
    }

    // Call the interpreter function
    explainCode(code);

    return 0;
}
