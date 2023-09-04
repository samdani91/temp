#include <iostream>
#include "tokenHeader.h"
#include "interpret.h"

int main()
{
    string inputCode = readInputCode(); // Read the input code from "sourceCode.c"
    int totalLines = inputCodeInLineByLine(inputCode); // Tokenize the input code and get the total number of lines

    tokenization(totalLines); // Perform tokenization and write the tokens to "TokenFile.txt"

    cout<<"\t\t\t---------------Interpretation----------------"<<endl;
    cout<<endl;
    interpret();

    return 0;
}
