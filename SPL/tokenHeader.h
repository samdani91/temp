#ifndef HEADERFILE_H
#define HEADERFILE_H

#include<bits/stdc++.h>
using namespace std;

#define parameterStruct                   vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,\
                                          vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses

struct perLinestruct{
    int line;
    string text;
};

struct func {
    int startLine;
    int endLine;
    string returnType;
    vector < string > parameter;
    vector < string > parameterType;
    int statement_text_start;
    int statement_text_end;
    string fTokens;
};

struct for_struct {
    int startLine;
    int endLine;
    vector < string > condition;
    vector < string > conditionType;
    vector < string > change;
    vector < string > changeType;
    vector < string > initialize;
    vector < string > initializeType;
    int statement_text_start;
    int statement_text_end;
};

struct while_struct {
    int startLine;
    int endLine;
    vector < string > condition;
    vector < string > conditionType;
    int statement_text_start;
    int statement_text_end;
};

struct do_while_struct {
    int startLine;
    int endLine;
    vector < string > condition;
    vector < string > conditionType;
    int statement_text_start;
    int statement_text_end;
};

struct else_struct {
    int startLine;
    int endLine;
    int statement_text_start;
    int statement_text_end;
};

struct else_if_struct {
    int startLine;
    int endLine;
    int statement_text_start;
    int statement_text_end;
    vector < string > condition;
    vector < string > conditionType;
};
struct if_struct {
    int startLine;
    int endLine;
    int statement_text_start;
    int statement_text_end;
    vector < string > condition;
    vector < string > conditionType;
    vector < else_struct > elses;
    vector < else_if_struct > if_elses;
};

//tokenSupport file's function prototype
string trim_left( string st, char ch );
string trim_right( string st, char ch );
string trim_both( string st, char ch );
bool isDigit( char ch );
bool isCapitalLetter( char ch );
bool isSmallLetter( char ch );
bool isLetter( char ch );
bool isNumber( string str );
string to_str( int number );
int strToint( string str );
bool validVariableName( string str );
bool operatorCheck( char ch );
bool operatorCheckdup( char ch );
bool isItInteger( string check );
bool isItDouble( string check );

//LineByLineSyntaxErrorChecking file's function prototype
void lineByLineSyntaxErrorChecking( int totalLine, parameterStruct );
void initialize_Checking( int line, int totalLine, parameterStruct );
void find_MAIN_function( int totalLine, parameterStruct );


// Tokenization file's function prototype
string keyword_identifier_number_check( int l, int col, string &check );
void tokenization( int totalLine );
string readInputCode( );
int inputCodeInLineByLine( string codeText );
string getPrintString( string item, int l, int col );


#endif