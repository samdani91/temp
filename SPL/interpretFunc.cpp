#include <bits/stdc++.h>
#include "interpret.h"
using namespace std;

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
map<string,string>dataType={{"int","integer"},
                            {"float","floating point"},
                            {"char","string"}};
unordered_map<string, float> traceVar;

bool open, isMain = false;

int main()
{

    ifstream file("TokenFile.txt");

    if (!file.is_open())
    {
        cout << "Failed to open the file." << endl;
        exit(0);
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
            unordered_multimap<string,string>map;
            while (currlineNum == lineNum)
            {
                mp.insert(make_pair(tokenType, tokenValue));
                map.insert(make_pair(tokenType, tokenValue));
                line.clear();
                getline(file, line);
                istringstream iss(line);
                iss >> tokenType >> tokenValue >> currlineNum;
            }     
            if(isArray(map)){
                // cout<<"IsAraay or IsString"<<endl;
                readArray(map,lineNum);
    
            }
            else {
                read_var(mp, lineNum);
            }
            mp.clear();
            map.clear();
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
            cout << "In line " << lineNum+1 << " >> "
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
            cout << "In line " << lineNum+1 << " >> "
                 << tokenValue << " closing of else block" << endl;
        }
        else if (tokenType == "keyword" && tokenValue == "for" && isMain == true)
        {   
            cout << "In line " << lineNum+1 << " >> "
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
                // cout<<tokenType<<" "<<tokenValue<<endl;
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
            cout << "In line " << lineNum+1 << " >> "
                 << tokenValue << " closing of for loop block" << endl;
            
        }
        else if (tokenType == "keyword" && tokenValue == "while" && isMain == true)
        {   
            cout << "In line " << lineNum+1 << " >> "
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
            cout << "In line " << lineNum+1 << " >> "
                 << tokenValue << " closing of while loop block" << endl;
            
        }
        else if (tokenType == "keyword" && tokenValue == "return" && isMain == true)
        {
            cout << "In line " << lineNum+1  << " >> "
                 << "It returns ";
            line.clear();
            getline(file, line);
            istringstream iss(line);
            iss >> tokenType >> tokenValue >> currlineNum;
            cout << tokenValue << " and program ends" << endl;
        }
        else
        {
            getline(file, line);
        }
    }


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
            cout << "In line " << lineNum+1 << " >> " << tokenValue << " header file" << endl;
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
        cout << "In line " << lineNum+1 << " >> " << tokenValue << " function and return type " << tempTokenValue << endl;
        open = true;
        isMain = true;
    }
}
void check_open_bracket(int lineNum, string tokenValue,string keyword)
{   
    if(keyword=="for")
    {
        cout << "In line " << lineNum+1 << " >> " << tokenValue << " opening curly braces of for loop block" << endl;
    }
    else if(keyword=="while")
    {
        cout << "In line " << lineNum+1 << " >> " << tokenValue << " opening curly braces of while loop block" << endl;
    }
    else if(keyword=="if")
    {
        cout << "In line " << lineNum+1 << " >> " << tokenValue << " opening curly braces of if block" << endl;
    }
    else if (keyword == "main")
    {
        cout << "In line " << lineNum+1 << " >> " << tokenValue << " opening curly braces of main function" << endl;
        open = false;
    }
}
void read_var(unordered_map<string, string> mp, int lineNum)
{   
    auto it = mp.find("integer");
    auto it2=mp.find("float");
    auto it3=mp.find("operator");

    if(it==mp.end() && it2==mp.end() && it3->second != "*"){
        cout << "In line " << lineNum+1 << " >> "
             << "This a " << dataType[mp["keyword"]] << " variable " << mp["identifier"]<< endl;
        traceVar.insert(make_pair(mp["identifier"], 0));
    }
    else if(it3!=mp.end() and it3->second == "*"){
        cout << "In line " << lineNum+1 << " >> "
             << "This a " << dataType[mp["keyword"]] << " pointer variable " << mp["identifier"]<< endl;
    }
    else{
        if (it != mp.end())
        {
            cout << "In line " << lineNum+1 << " >> "
                    << "This a " << dataType[mp["keyword"]] << " variable " << mp["identifier"] << " and value assigned to it is " << mp["integer"] << endl;
            traceVar.insert(make_pair(mp["identifier"], stoi(mp["integer"])));
        }

        it = mp.find("float");
        if (it != mp.end())
        {
            cout << "In line " << lineNum+1 << " >> "
                    << "This a " << dataType[mp["keyword"]] << " variable " << mp["identifier"] << " and value assigned to it is " << mp["float"] << endl;

            try
            {
                /* code */
                 traceVar.insert(make_pair(mp["identifier"], stof(mp["float"])));
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        }
    }
}
void read_condition(unordered_map<string, string> condition, int lineNum)
{   
    // for(auto it:condition){
    //     cout<<it.first<<" "<<it.second<<endl;
    // }
    auto it = condition.find("integer");
    int checkInt = 0,checkFloat=0;
    if (it != condition.end())
    {
        cout << "In line " << lineNum+1 << " >> "
             << "There is a " << condition["keyword"] << " condition that is true when " << condition["identifier"] << " is " << operators[condition["operator"]] << condition["integer"] << endl;
        checkInt = 1;
    }
    else
    {
        it = condition.find("float");
        if (it != condition.end())
        {unordered_map<string, float> traceVar;
            cout << "In line " << lineNum+1 << " >> "
                 << "There is a " << condition["keyword"] << " condition that is true when " << condition["identifier"] << " is " << operators[condition["operator"]] << condition["float"] << endl;
        }
        checkFloat=1;
    }
    float temp = traceVar[condition["identifier"]];
    float temp2;
    if (checkInt)
    {
        // temp2 = stof(condition["integer"]);
        try
        {
            /* code */
            temp2 = stof(condition["integer"]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    else if(checkFloat)
    {   
        //cout<<condition["float"]<<endl;
        // temp2 = stof(condition["float"]);
        try
        {
            /* code */
            temp2 = stof(condition["float"]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
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
    bool isArr=false;
    for (auto it = range.first; it != range.second; ++it)
    {   
        if (it->first == "string")
        {
            string temp=it->second;
            if (it->second == "%d" || it->second == "%f")
            {
                format_specifier = it->second;
                check_format_spec = 1;
                break;
            }
            else if(temp.find("%d\n")!=string::npos){
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

    range=print.equal_range("operator");
    for (auto it = range.first; it != range.second; ++it)
    {
        if (it->first == "operator")
        {
            if(it->second=="[" or it->second=="]"){
                isArr=true;
                break;
            }
        }
    }

    range = print.equal_range("identifier");
    for (auto it = range.first; it != range.second; ++it)
    {   
        if (it->first == "identifier" and !isArray)
        {
            var = it->second;
            break;
        }
        if(isArray){
            string temp=it->second;
            if(temp.size()==1 and temp[0]>=96 and temp[0]<=127) continue;
            else{
                var=it->second;
                break;
            }
        }
    }
    if (check_format_spec and !isArr)
    {
        cout << "In line " << lineNum+1 << " >> "
             << "This a print statement and which prints a " << fm_spec[format_specifier] << var << " = " << traceVar[var] << endl;
    }
    else if(check_format_spec and isArr)
    {
        cout << "In line " << lineNum + 1 << " >> "
             << "Printing "<< var << " element"<< endl;
    }
    else
    {
        cout << "In line " << lineNum+1 << " >> "
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
    bool isArray;
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

    range=input.equal_range("operator");
    for (auto it = range.first; it != range.second; ++it)
    {
        if (it->first == "operator")
        {
            if(it->second=="[" or it->second=="]"){
                isArray=true;
                break;
            }
        }
    }

    range = input.equal_range("identifier");
    for (auto it = range.first; it != range.second; ++it)
    {   
        if (it->first == "identifier" and !isArray)
        {
            var = it->second;
            break;
        }
        if(isArray){
            string temp=it->second;
            if(temp.size()==1 and temp[0]>=96 and temp[0]<=127) continue;
            else{
                var=it->second;
                break;
            }
        }
    }


    if (check_format_spec and !isArray)
    {
        cout << "In line " << lineNum + 1 << " >> "
             << "This a scanf statement and takes input a " << fm_spec[format_specifier] << "and assigned to variable "<< var <<  endl;
    }
    else if (check_format_spec and isArray)
    {
        cout << "In line " << lineNum + 1 << " >> "
             << "Taking input of "<< var << " element"<< endl;
    }
    
}
void read_for(unordered_map<string, string> statements, int lineNum)
{
    read_var(statements,lineNum);
    if(statements["operator"]=="++"){
        cout << "In line " << lineNum+1 << " >> and "
                 <<statements["identifier"]<<" is increasing by one"<<endl;
    }

}
void read_for_block(unordered_multimap<string, string> statements,unordered_map<string,string>condition,
                    unordered_map<string,string>modification, int lineNum)
{   

    
    string keyTodelete = "identifier";
    int check_print = 0;
    int check_scan = 0;

    bool isArr=false;

    auto range = statements.equal_range(keyTodelete);
    for (auto it = range.first; it != range.second; ++it)
    {
        if (it->second == "printf" or it->second == "scanf")
        {
            if(it->second == "printf") check_print = 1;
            if(it->second == "scanf") check_scan = 1;

            statements.erase(it);
            break;
        }
    }

    range=statements.equal_range("operator");
    for (auto it = range.first; it != range.second; ++it)
    {
        if (it->first == "operator")
        {
            if(it->second=="[" or it->second=="]"){
                isArr=true;
                break;
            }
        }
    }
    // for(auto it:statements){
    //     cout<<it.first<<" "<<it.second<<endl;
    // }

    if (check_print and !isArr){
        int limit=stoi(condition["integer"]);
        // cout<<limit<<endl;
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
    else if(check_print and isArr){
        read_printf(statements,lineNum);
    }

    if(check_scan){
        read_scanf(statements,lineNum);
    }
}
void read_while(unordered_map<string, string> statements, int lineNum)
{   
    read_condition(statements,lineNum);
    
}
void read_while_block(unordered_multimap<string, string> statements,unordered_map<string,string>condition,int lineNum)
{
    unordered_map<string,string>modification;
    static unordered_multimap<string, string> tempStatements;
    string op="";
    bool checkModification=false;
    static int check_print = 0,check_scan=0,lineNo;
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
        for (auto it = range.first; it != range.second; ++it){
            if (it->second == "printf" or it->second == "scanf"){
                if(it->second == "printf") check_print = 1;
                if(it->second == "scanf") check_scan = 1;

                statements.erase(it);
                break;
            }
        }
        
        for(auto it:statements){
            tempStatements.insert(make_pair(it.first,it.second));
        }
    }

    if(checkModification==true){
        if(check_scan){
            read_scanf(tempStatements,lineNum);
        }
        if(check_print){//here
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
}

bool isArray(unordered_multimap<string, string> map)
{   
    string toFind="operator";
    auto range=map.equal_range(toFind);
    for (auto it = range.first; it != range.second; ++it)
    {
        if (it->second == "[" or it->second == "]")
        {
            return true;
        }
    }

    return false;  

}
void readArray(unordered_multimap<string, string> statements, int lineNum)
{

    string key="keyword";
    auto range=statements.equal_range(key);

    string data_type=range.first->second;

    range=statements.equal_range("identifier");
    auto range2=statements.equal_range("integer");

    vector<string>v;
    for (auto it = range.first; it != range.second; ++it) {
        v.push_back(it->second);
    }
    string size;
    if(v.size()==1){
        v[1]=v[0];
        size=range2.first->second;
    }else{
        size=v[0];
    }

    cout << "In line " << lineNum+1 << " >> "
             << "This a " << dataType[data_type] << " array variable " << v[1]<< " and size is "<<size<<endl;

    
}