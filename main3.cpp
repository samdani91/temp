#include<bits/stdc++.h>
using namespace std;


vector<string> blankLineRemover(vector<string> code);
void lineWiseBlankLineRemover(vector<string> &blankLineRemoved,string line,int startIndex,int finishIndex);
vector<string> removeFrontWhiteSpace(vector<string> code);
void lineWiseWhiteSpaceRemover(vector<string>&frontWhiteSpaceRemovedCode,string line,string &whiteSpaceRemovedLine, int startIndex, int finishingIndex);


int main()
{
    ifstream file("test.c");
    string line;
    vector<string> temp;
    while(getline(file,line)){
        temp.push_back(line);

    }
    temp=removeFrontWhiteSpace(temp);
    temp=blankLineRemover(temp);
    for(int i=0;i<temp.size();i++){
        cout<<temp[i]<<endl;
    }

    return 0;
}
vector<string> removeFrontWhiteSpace(vector<string> code){
    vector<string>frontWhiteSpaceRemovedCode;
    string line;
    string whiteSpaceRemovedLine;
    for(int i=0; i<code.size(); i++){
        line=code[i];
        lineWiseWhiteSpaceRemover(frontWhiteSpaceRemovedCode,line,whiteSpaceRemovedLine, 0, line.size());
    }
    return frontWhiteSpaceRemovedCode;
}

void lineWiseWhiteSpaceRemover(vector<string>&frontWhiteSpaceRemovedCode,string line,string &whiteSpaceRemovedLine, int startIndex, int finishingIndex){
    int i = startIndex;
    while(i<finishingIndex && line[i]==' '){
        i++;
    }
    whiteSpaceRemovedLine = line.substr(i);
    frontWhiteSpaceRemovedCode.push_back(whiteSpaceRemovedLine);
}

vector<string> blankLineRemover(vector<string> code){
    vector<string> blankLineRemoved;
    string line;
    for(int i=0;i<code.size();i++){
        line=code[i];
        lineWiseBlankLineRemover(blankLineRemoved,line,0,line.size());
    }
    return blankLineRemoved;

}

void lineWiseBlankLineRemover(vector<string> &blankLineRemoved,string line,int startIndex,int finishIndex){
    int i=startIndex;
    while(i<finishIndex && line[i]!=' ') i++;
    if(i!=finishIndex){
        blankLineRemoved.push_back(line);
    }
}