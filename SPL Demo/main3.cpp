#include<bits/stdc++.h>
using namespace std;


vector<string> blankLineRemover(vector<string> code);
void lineWiseBlankLineRemover(vector<string> &blankLineRemoved,string line,int startIndex,int finishIndex);
vector<string> removeFrontWhiteSpace(vector<string> code);
void lineWiseWhiteSpaceRemover(vector<string>&frontWhiteSpaceRemovedCode,string line,string &whiteSpaceRemovedLine, int startIndex, int finishingIndex);
void checkHeaders(vector<string>code);

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
    
    // for(int i=0;i<temp.size();i++){
    //     cout<<temp[i]<<endl;
    // }
    checkHeaders(temp);


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
    if(line!=""){
        blankLineRemoved.push_back(line);
    }
}

void checkHeaders(vector<string>code){
    vector<string>includeHeaders={"stdio.h","stdlib.h","math.h","string.h"};
    string line;
    string header;
    for(int i=0;i<code.size();i++){
        line=code[i];
        if(line.find("#include")!=string::npos){
            int start=line.find("<");
            int end=line.find(">");

            if(start!=string::npos && end!=string::npos && start<end){
                header+=line.substr(start+1,end-start-1);
                auto it=find(includeHeaders.begin(),includeHeaders.end(),header);
                if(it!=includeHeaders.end()){
                    cout<<"Line "<<i+1<<": "<<"This line contains a header file: "<<*it<<endl;
                    header="";
                }
            }
        }
        else{
            if(i==0){
                cout << "\033[31m"; //red text
                cout<<"Waring: No header in first line"<<endl;
                cout << "\033[0m";  //default text
            }
            break;
        }
        line="";
    }
}

void findMain(vector<string>code){
    vector<string>dataType={"void","int"};
    string line;
    string type;
    string name;
    for(int i=0;i<code.size();i++){
        line=code[i];
        int checkDataType=line.find("int");
        if(checkDataType==string::npos) {
            checkDataType=line.find("void");
        }
        if(checkDataType!=string::npos){
            
        }

    }
}