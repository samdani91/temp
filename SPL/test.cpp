#include <bits/stdc++.h>
using namespace std;

void read_headers(string line);
void read_main_prototype(string line, string tokenValue);
void check_open_bracket(int lineNum, string tokenValue,string keyword);
void read_var(unordered_map<string, string> map, int currlineNum);
void read_condition(unordered_map<string, string> condition, int lineNum);
void read_if_else_block(unordered_multimap<string, string> statements, int lineNum);
void read_printf(unordered_multimap<string, string> print, int lineNum);
void read_scanf(unordered_multimap<string, string> input, int lineNum);
void read_for(unordered_map<string, string> statements, int lineNum);
void read_while(unordered_map<string, string> statements, int lineNum);
void read_for_block(unordered_multimap<string, string> statements,unordered_map<string,string>condition,unordered_map<string,string>modification, int lineNum);
void read_while_block(unordered_multimap<string, string> statements,unordered_map<string,string>condition,int lineNum);


vector<string> header = {"stdio.h", "conio.h", "stdlib.h", "math.h", "string.h"};
vector<string>operatorSign={"++","--","+=","-="};
map<string, string> operators = {{"!=", "not equal "},
                                 {"==", "equal "},
                                 {">=", "greater than or equal "},
                                 {"<=", "less than or equal "},
                                 {">", "greater than "},
                                 {"<", "less than "}};
map<string, string> fm_spec = {{"%d", "integer "},
                                {"%dn", "integer in every new line "},
                               {"%f", "float "},
                               {"%fn", "float in every new line "},
                                {"%c", "character "}};
unordered_map<string, float> traceVar;

bool open, isMain = false;

int main()
{

    ifstream file("TokenFile.txt");

    if (!file.is_open())
    {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    string line, temp;


    getline(file, line);

    while (!file.eof())
    {

        istringstream iss(line);
        string tokenType, tokenValue, tempTokenValue;
        int lineNum, currlineNum;

        iss >> tokenType >> tokenValue >> lineNum;
        tempTokenValue = tokenValue;
        currlineNum = lineNum;

        if (tokenValue == "#")
        {
            while (currlineNum == lineNum)
            {
                read_headers(line);
                line.clear();
                getline(file, line);
                istringstream iss(line);
                iss >> tokenType >> tokenValue >> currlineNum;
            }
        }
        else if (tokenType == "keyword" && isMain == false)
        {
            while (currlineNum == lineNum)
            {
                line.clear();
                getline(file, line);
                istringstream iss(line);
                iss >> tokenType >> tokenValue >> currlineNum;
                read_main_prototype(line, tempTokenValue);
            }
        }
        else if (open == true)
        {
            check_open_bracket(lineNum, tokenValue,"main");
        }
        else if(tokenType=="identifier" && (tokenValue=="printf" || tokenValue=="scanf") && isMain==true)
        {   
            string line_tokenValue=tokenValue;
            unordered_multimap<string, string> input;
            while (currlineNum == lineNum)
            {   
                
                if (tokenValue != "(" && tokenValue != ")" && tokenValue != ";")
                {
                    input.insert(make_pair(tokenType, tokenValue));
                }
                line.clear();
                getline(file, line);
                istringstream iss(line);
                iss >> tokenType >> tokenValue >> currlineNum;
            }
            if(line_tokenValue=="printf"){
                read_printf(input,lineNum);
            }else{
                read_scanf(input,lineNum);
            }

        }
        else if (tokenType == "keyword" && tokenValue != "if" && tokenValue != "else" && tokenValue != "return" && tokenValue != "for" && tokenValue != "while" && isMain == true)
        {
            unordered_map<string, string> mp;
            while (currlineNum == lineNum)
            {
                mp.insert(make_pair(tokenType, tokenValue));
                line.clear();
                getline(file, line);
                istringstream iss(line);
                iss >> tokenType >> tokenValue >> currlineNum;
            }
            read_var(mp, lineNum);
            mp.clear();
        }
        else if (tokenType == "keyword" && tokenValue == "if" && isMain == true)
        {   
            unordered_map<string, string> condition;
            unordered_multimap<string, string> statements;
            bool checkOpenCurlyBrace=false;
            int openCurlyBraceLinenum;
            while (currlineNum == lineNum)
            {   
                
                if (tokenValue != "(" && tokenValue != ")" && tokenValue != "{")
                {
                    condition.insert(make_pair(tokenType, tokenValue));
                }
                line.clear();
                getline(file, line);
                istringstream iss(line);
                iss >> tokenType >> tokenValue >> currlineNum;
                if(tokenValue=="{")
                {   
                    checkOpenCurlyBrace=true;
                    openCurlyBraceLinenum=currlineNum;

                }
            }
            read_condition(condition, lineNum);
            condition.clear();
            if(checkOpenCurlyBrace){
                check_open_bracket(openCurlyBraceLinenum,"{","if");
            }
            lineNum++;
            while (tokenValue != "}")
            {
                while (currlineNum == lineNum)
                {
                    if (tokenValue != "(" && tokenValue != ")" && tokenValue != ";")
                        statements.insert(make_pair(tokenType, tokenValue));
                    line.clear();
                    getline(file, line);
                    istringstream iss(line);
                    iss >> tokenType >> tokenValue >> currlineNum;
                }
                read_if_else_block(statements, lineNum);
                statements.clear();
                lineNum = currlineNum;
            }
            cout << "In line " << lineNum << " >> "
                 << tokenValue << " closing of if block" << endl;
        }
        else if (tokenType == "keyword" && tokenValue == "else" && isMain == true)
        {
            unordered_multimap<string, string> statements;
            cout << "In line " << lineNum << " >> "
                 << "Starting of " << tokenValue << " block" << endl;
            line.clear();
            getline(file, line);
            line.clear();
            getline(file, line);
            istringstream iss(line);
            iss >> tokenType >> tokenValue >> currlineNum;
            while (tokenValue != "}")
            {
                while (currlineNum == lineNum)
                {
                    if (tokenValue != "(" && tokenValue != ")" && tokenValue != ";")
                        statements.insert(make_pair(tokenType, tokenValue));
                    line.clear();
                    getline(file, line);
                    istringstream iss(line);
                    iss >> tokenType >> tokenValue >> currlineNum;
                }
                read_if_else_block(statements, lineNum);
                statements.clear();
                lineNum = currlineNum;
            }
            cout << "In line " << lineNum << " >> "
                 << tokenValue << " closing of else block" << endl;
        }
        else if (tokenType == "keyword" && tokenValue == "for" && isMain == true)
        {   
            cout << "In line " << lineNum << " >> "
         << "Starting of for loop" << endl;
            line.clear();
            getline(file, line);
            istringstream iss(line);
            iss >> tokenType >> tokenValue >> currlineNum;
            unordered_map<string, string> statements;
            unordered_map<string, string> condition;
            unordered_map<string, string> modification;
            while (tokenValue != ";")
            {
                if (tokenValue != "(")
                    statements.insert(make_pair(tokenType, tokenValue));
                line.clear();
                getline(file, line);
                istringstream iss(line);
                iss >> tokenType >> tokenValue >> currlineNum;
            }
            read_for(statements, lineNum);
            statements.clear();
            getline(file,line);
            istringstream issNew(line);
            issNew >> tokenType >> tokenValue >> currlineNum;
            while (tokenValue != ";")
            {
                
                condition.insert(make_pair(tokenType, tokenValue));
                line.clear();
                getline(file, line);
                istringstream iss(line);
                iss >> tokenType >> tokenValue >> currlineNum;
            }
            read_condition(condition, lineNum);
            statements.clear();
            getline(file,line);
            istringstream issNew2(line);
            issNew2 >> tokenType >> tokenValue >> currlineNum;
            while (tokenValue != ")")
            {
                
                modification.insert(make_pair(tokenType, tokenValue));
                line.clear();
                getline(file, line);
                istringstream iss(line);
                iss >> tokenType >> tokenValue >> currlineNum;
            }
            read_for(modification, lineNum);
            statements.clear();
            unordered_multimap<string,string>statements2;
            getline(file,line);
            istringstream issNew3(line);
            issNew3 >> tokenType >> tokenValue >> currlineNum;
            check_open_bracket(currlineNum,tokenValue,"for");
            getline(file,line);
            istringstream issNew4(line);
            issNew4 >> tokenType >> tokenValue >> currlineNum;
            lineNum=currlineNum;
            while(lineNum==currlineNum){
                if (tokenValue != "(" && tokenValue != ")" && tokenValue != ";" && tokenValue!=",")
                statements2.insert(make_pair(tokenType, tokenValue));
                line.clear();
                getline(file, line);
                istringstream iss(line);
                iss >> tokenType >> tokenValue >> currlineNum;
            }
            read_for_block(statements2,condition,modification,lineNum);
            lineNum=currlineNum;
            cout << "In line " << lineNum << " >> "
                 << tokenValue << " closing of for loop block" << endl;
            
        }
        else if (tokenType == "keyword" && tokenValue == "while" && isMain == true)
        {   
            cout << "In line " << lineNum << " >> "
         << "Starting of while loop" << endl;
            line.clear();
            getline(file, line);
            istringstream iss(line);
            iss >> tokenType >> tokenValue >> currlineNum;
            unordered_map<string, string> condition;
            unordered_multimap<string, string> statements;
            while (tokenValue != ")")
            {
                if (tokenValue != "(")
                    condition.insert(make_pair(tokenType, tokenValue));
                line.clear();
                getline(file, line);
                istringstream iss(line);
                iss >> tokenType >> tokenValue >> currlineNum;
            }
            read_while(condition,lineNum);
            getline(file,line);
            istringstream issNew(line);
            issNew >> tokenType >> tokenValue >> currlineNum;
            check_open_bracket(currlineNum,tokenValue,"while");
            getline(file,line);
            istringstream issNew2(line);
            issNew2 >> tokenType >> tokenValue >> currlineNum;
            
            while(tokenValue!="}"){
                lineNum=currlineNum;
                while(lineNum==currlineNum){
                    if (tokenValue != "(" && tokenValue != ")" && tokenValue != ";" && tokenValue!=",")
                    statements.insert(make_pair(tokenType, tokenValue));
                    line.clear();
                    getline(file, line);
                    istringstream iss(line);
                    iss >> tokenType >> tokenValue >> currlineNum;
                }
                read_while_block(statements,condition,lineNum);
                statements.clear();

            }
            lineNum=currlineNum;
            cout << "In line " << lineNum << " >> "
                 << tokenValue << " closing of while loop block" << endl;
            
        }
        else if (tokenType == "keyword" && tokenValue == "return" && isMain == true)
        {
            cout << "In line " << lineNum << " >> "
                 << "It returns ";
            line.clear();
            getline(file, line);
            istringstream iss(line);
            iss >> tokenType >> tokenValue >> currlineNum;
            cout << tokenValue << " and program ends" << endl;
        }
        else
        {
            // cout<<line<<endl;
            getline(file, line);
            //cout<<line<<endl;
        }
    }

    return 0;
}
void read_headers(string line)
{
    string tokenValue, tokenType;
    int lineNum;
    istringstream iss(line);
    iss >> tokenType >> tokenValue >> lineNum;
    for (int i = 0; i < header.size(); i++)
    {
        if (tokenValue == header[i])
        {
            cout << "In line " << lineNum << " >> " << tokenValue << " header file" << endl;
        }
    }
}

void read_main_prototype(string line, string tempTokenValue)
{
    string tokenValue, tokenType;
    int lineNum;
    istringstream iss(line);
    iss >> tokenType >> tokenValue >> lineNum;

    if (tokenValue == "main")
    {
        cout << "In line " << lineNum << " >> " << tokenValue << " function and return type " << tempTokenValue << endl;
        open = true;
        isMain = true;
    }
}
void check_open_bracket(int lineNum, string tokenValue,string keyword)
{   
    if(keyword=="for")
    {
        cout << "In line " << lineNum << " >> " << tokenValue << " opening curly braces of for loop block" << endl;
    }
    else if(keyword=="while")
    {
        cout << "In line " << lineNum << " >> " << tokenValue << " opening curly braces of while loop block" << endl;
    }
    else if(keyword=="if")
    {
        cout << "In line " << lineNum << " >> " << tokenValue << " opening curly braces of if block" << endl;
    }
    else if (keyword == "main")
    {
        cout << "In line " << lineNum << " >> " << tokenValue << " opening curly braces of main function" << endl;
        open = false;
    }
}
void read_var(unordered_map<string, string> mp, int lineNum)
{
    // for(auto it:mp){
    //     cout<<it.first<<" "<<it.second<<endl;
    // }
    auto it = mp.find("integer");
    if (it != mp.end())
    {
        cout << "In line " << lineNum << " >> "
             << "This a " << mp["keyword"] << " variable " << mp["identifier"] << " and value assigned to it is " << mp["integer"] << endl;
        traceVar.insert(make_pair(mp["identifier"], stoi(mp["integer"])));
    }
    else
    {
        it = mp.find("float");
        if (it != mp.end())
        {
            cout << "In line " << lineNum << " >> "
                 << "This a " << mp["keyword"] << " variable " << mp["identifier"] << " and value assigned to it is " << mp["float"] << endl;
            traceVar.insert(make_pair(mp["identifier"], stof(mp["float"])));
        }
    }
}
void read_condition(unordered_map<string, string> condition, int lineNum)
{
    auto it = condition.find("integer");
    int checkInt = 0;
    if (it != condition.end())
    {
        cout << "In line " << lineNum << " >> "
             << "There is a " << condition["keyword"] << " condition that is true when " << condition["identifier"] << " is " << operators[condition["operator"]] << condition["integer"] << endl;
        checkInt = 1;
    }
    else
    {
        it = condition.find("float");
        if (it != condition.end())
        {
            cout << "In line " << lineNum << " >> "
                 << "There is a " << condition["keyword"] << " condition that is true when " << condition["identifier"] << " is " << operators[condition["operator"]] << condition["float"] << endl;
        }
    }
    float temp = traceVar[condition["identifier"]];
    float temp2;
    if (checkInt)
    {
        temp2 = stof(condition["integer"]);
    }
    else
    {
        temp2 = stof(condition["float"]);
    }
    if (condition["operator"] == "!=")
    {
        if (temp != temp2)
        {
            cout << "\t\tand Condition is true" << endl;
        }
        else
        {
            cout << "\t\tand Condition is false" << endl;
        }
    }
    else if (condition["operator"] == "==")
    {
        if (temp == temp2)
        {
            cout << "\t\tand Condition is true" << endl;
        }
        else
        {
            cout << "\t\tand Condition is false" << endl;
        }
    }
    else if (condition["operator"] == ">=")
    {
        if (temp >= temp2)
        {
            cout << "\t\tand Condition is true" << endl;
        }
        else
        {
            cout << "\t\tand Condition is false" << endl;
        }
    }
    else if (condition["operator"] == "<=")
    {
        if (temp <= temp2)
        {
            cout << "\t\tand Condition is true" << endl;
        }
        else
        {
            cout << "\t\tand Condition is false" << endl;
        }
    }
    else if (condition["operator"] == ">")
    {
        if (temp > temp2)
        {
            cout << "\t\tand Condition is true" << endl;
        }
        else
        {
            cout << "\t\tand Condition is false" << endl;
        }
    }
    else if (condition["operator"] == "<")
    {
        if (temp < temp2)
        {
            cout << "\t\tand Condition is true" << endl;
        }
        else
        {
            cout << "\t\tand Condition is false" << endl;
        }
    }
}
void read_if_else_block(unordered_multimap<string, string> statements, int lineNum)
{
    // for(auto it:statements){
    //     cout<<it.first<<" "<<it.second<<endl;
    // }
    string keyTodelete = "identifier";
    string valueTodelete = "printf";
    int check_print = 0;

    auto range = statements.equal_range(keyTodelete);
    for (auto it = range.first; it != range.second; ++it)
    {
        if (it->second == valueTodelete)
        {
            check_print = 1;
            statements.erase(it);
            break;
        }
    }
    // cout<<"new"<<endl;
    // for(auto it:statements){
    //     cout<<it.first<<" "<<it.second<<endl;
    // }
    if (check_print)
        read_printf(statements, lineNum);
}
void read_printf(unordered_multimap<string, string> print, int lineNum)
{
    auto range = print.equal_range("string");
    string format_specifier;
    string var;
    string output;
    int check_format_spec = 0;
    for (auto it = range.first; it != range.second; ++it)
    {   
        if (it->first == "string")
        {
            string temp=it->second;
            cout<<temp<<endl;
            if (it->second == "%d" || it->second == "%f")
            {
                format_specifier = it->second;
                check_format_spec = 1;
                break;
            }
            else if(it->second.find("%d\n") != string::npos){
                //cout<<temp<<endl;
                format_specifier ="%dn";
                check_format_spec = 1;
                break;
            }
            else if(temp.find("%f\n")!=string::npos){
                format_specifier ="%fn";
                check_format_spec = 1;
                break;
            }
            else
            {
                output = it->second;
                break;
            }
        }
    }
    range = print.equal_range("identifier");
    for (auto it = range.first; it != range.second; ++it)
    {
        if (it->first == "identifier")
        {
            var = it->second;
            break;
        }
    }
    if (check_format_spec)
    {
        cout << "In line " << lineNum << " >> "
             << "This a print statement and which prints a " << fm_spec[format_specifier] << var << " = " << traceVar[var] << endl;
    }
    else
    {
        cout << "In line " << lineNum << " >> "
             << "This a print statement and which prints " << output << endl;
    }
}

void read_scanf(unordered_multimap<string, string> input, int lineNum)
{
    auto range = input.equal_range("string");
    string format_specifier;
    string var;
    string output;
    int check_format_spec = 0;
    for (auto it = range.first; it != range.second; ++it)
    {   
        if (it->first == "string")
        {
            string temp=it->second;
            if (it->second == "%d" || it->second == "%f" || it->second == "%c")
            {
                format_specifier = it->second;
                check_format_spec = 1; 
                break;
            }
            else
            {
                output = it->second;
                break;
            }
        }
    }
    range = input.equal_range("identifier");
    for (auto it = range.first; it != range.second; ++it)
    {
        if (it->first == "identifier")
        {
            var = it->second;
            break;
        }
    }
    if (check_format_spec)
    {
        cout << "In line " << lineNum + 1 << " >> "
             << "This a scanf statement and takes input a " << fm_spec[format_specifier] << "and assigned to variable "<< var <<  endl;
    }
    
}
void read_for(unordered_map<string, string> statements, int lineNum)
{
    // for(auto it:statements){
    //     cout<<it.first<<" "<<it.second<<endl;
    // }
    
    read_var(statements,lineNum);
    if(statements["operator"]=="++"){
        cout << "In line " << lineNum << " >> and "
                 <<statements["identifier"]<<" is increasing by one"<<endl;
    }

}
void read_for_block(unordered_multimap<string, string> statements,unordered_map<string,string>condition,
                    unordered_map<string,string>modification, int lineNum)
{
    // for(auto it:statements){
    //     cout<<it.first<<" "<<it.second<<endl;
    // }
    string keyTodelete = "identifier";
    string valueTodelete = "printf";
    int check_print = 0;

    auto range = statements.equal_range(keyTodelete);
    for (auto it = range.first; it != range.second; ++it)
    {
        if (it->second == valueTodelete)
        {
            check_print = 1;
            statements.erase(it);
            break;
        }
    }
    // cout<<"new"<<endl;
    // for(auto it:statements){
    //     cout<<it.first<<" "<<it.second<<endl;
    // }
    if (check_print){
        int limit=stoi(condition["integer"]);
        int i=(int) traceVar[modification["identifier"]];
        string controlOperator=condition["operator"];
        if(controlOperator=="<="){
            for(;i<=limit;i++)
            {   
                read_printf(statements, lineNum);
                traceVar[modification["identifier"]]++;
            }
        }
        else if(controlOperator=="<"){
            for(;i<limit;i++)
            {   
                read_printf(statements, lineNum);
                traceVar[modification["identifier"]]++;
            }
        }
        
    }
}

void read_while(unordered_map<string, string> statements, int lineNum)
{   

    read_condition(statements,lineNum);
    
}
void read_while_block(unordered_multimap<string, string> statements,unordered_map<string,string>condition,int lineNum)
{
    // for(auto it:statements){
    //     cout<<it.first<<" "<<it.second<<endl;
    // }
    unordered_map<string,string>modification;
    static unordered_multimap<string, string> tempStatements;
    string op="";
    bool checkModification=false;
    static int check_print = 0,lineNo;
    for(auto it:statements){
        for(auto it2:operatorSign){
            if(it.second==it2){
                op=it2;
                checkModification=true;
                break;
            }
        }
        if(checkModification==true) break;
    }

    if(checkModification==true){
        for(auto it:statements){
            modification.insert(make_pair(it.first,it.second));
        }
    }
    else{
        string keyTodelete = "identifier";
        string valueTodelete = "printf";
        lineNo=lineNum;
        auto range = statements.equal_range(keyTodelete);
        for (auto it = range.first; it != range.second; ++it)
        {
            if (it->second == valueTodelete)
            {
                check_print = 1;
                statements.erase(it);
                break;
            }
        }
        for(auto it:statements){
            tempStatements.insert(make_pair(it.first,it.second));
        }
    }

    if(checkModification==true){
        int limit=stoi(condition["integer"]);
        int i=(int) traceVar[modification["identifier"]];
        string controlOperator=condition["operator"];
        if(controlOperator=="<="){
            for(;i<=limit;i++)
            {   
                if (check_print){

                read_printf(tempStatements, lineNo);
                traceVar[modification["identifier"]]++;
                }
            }
        }
        else if(controlOperator=="<"){
            for(;i<limit;i++)
            {   
                if (check_print){

                read_printf(tempStatements, lineNo);
                traceVar[modification["identifier"]]++;
                }
            }
        }
    }
}
