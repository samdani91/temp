#include <bits/stdc++.h>
#include "tokenHeader.h"
using namespace std;

string trim_left(string st, char ch)
{
    while (st.size() && st[0] == ch)
    {
        st.erase(0, 1);
    }
    return st;
}
string trim_right(string st, char ch)
{
    while (st.size() && st[st.size() - 1] == ch)
    {
        st.erase(st.size() - 1, 1);
    }

    return st;
}
string trim_both(string st, char ch)
{
    st = trim_right(st, ch);
    st = trim_left(st, ch);

    return st;
}
bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}
bool isCapitalLetter(char ch)
{
    return ch >= 'A' && ch <= 'Z';
}
bool isSmallLetter(char ch)
{
    return ch >= 'a' && ch <= 'z';
}
bool isLetter(char ch)
{
    return isSmallLetter(ch) || isCapitalLetter(ch);
}
bool isNumber(string str){
    int i=0;
    while(str[i]!='\0'){
        if(!(isdigit(str[i])))
        {
            return false;
        }
    }
    return true;
}
string to_str(int number)
{
    string temp;
    while (number)
    {
        int lastDigit = number % 10;
        temp += '0' + lastDigit;
        number /= 10;
    }
    reverse(temp.begin(), temp.end());

    return temp;
}
int strToint(string str)
{
    int temp;
    int i = 0;
    while (str[i] != '\0')
    {
        temp *= 10;
        temp += str[i] - '0';
        i++;
    }
    return temp;
}
bool validVariableName(string str)
{
    if (!(isLetter(str[0]) || str[0] == '_'))
    {
        return false;
    }
    int i = 1;
    while (str[i] != '\0')
    {
        if (!(isLetter(str[i]) || isDigit(str[i]) || str[i] == '_'))
        {
            return false;
        }
        i++;
    }
    return true;
}
bool operatorCheck(char ch)
{
    if (ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '(' || ch == ')' || ch == '#' || ch == ';' || ch == ':' || ch == '?' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '&' || ch == '|' || ch == '!' || ch == '=' || ch == '<' || ch == '>' || ch == ',')
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool operatorCheckdup(char ch)
{
    if (ch == '+' || ch == '-' || ch == '&' || ch == '|' || ch == '=' || ch == '>' || ch == '<')
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool isItInteger(string check)
{
    int i = 0;
    while (check[i] != '\0')
    {
        if (!(isDigit(check[i])))
        {
            return false;
        }
        i++;
    }
    return true;
}
bool isItDouble(string check)
{
    int dot = 0;
    int i = 0;
    while (check[i] != '\0')
    {
        if (isDigit(check[i]))
        {
            continue;
        }
        if (check[i] == '.')
        {
            dot++;
        }
        else
        {
            return false;
        }

        i++;
    }
    return dot <= 1;
}