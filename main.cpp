#include<bits/stdc++.h>
using namespace std;

void showOutput(string line);
void mainFucntion(string line);

int main()
{
    ifstream file("test.c");

    if (!file.is_open())
    {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    string line;

    // getline(file, line);

    // showOutput(line);

    while (getline(file, line))
    {
        showOutput(line);

    }
    
    //cout<<line<<endl;

    return 0;
}
void showOutput(string line){
    int i=0;
    bool flag=false;
    bool space=false;
    bool scurly,ecurly;
    scurly=ecurly=false;
    string temp;
    if(line[i]=='#'){
        while(line[i]!='\0'){
        
            i++;
            while(line[i]!='<'){
                temp+=line[i];
                i++;
            }
            if(temp!="include"){
                cout<<"Error\n";
                return;
            }
            i++;
            temp="";
            while(line[i]!='>'){
                temp+=line[i];
                i++;
            }
        
            if(temp!="stdio.h"){
                cout<<"Error in stdio.h\n";
                return;
            }
            flag=true;
            i++;
        }
    }else if(line[i]==' ' || line[i]=='\t'){
        space=true;
        while(line[i]){    
            if(line[i]!=' ' || line[i]!='\t'){
                space=false;
                break;
            }
            i++;
        }
    }else if(line[i]=='{'){
        scurly=true;
    }
    else if(line[i]=='}'){
        ecurly=true;
    }

    if(flag) cout<<"this line got stdio.h"<<endl;
    else if(space) cout<<"this line is blank"<<endl;
    else if(scurly) cout<<"opening curly braces found"<<endl;
    else if(ecurly) cout<<"closing curly braces found"<<endl;
    else cout<<"other lines"<<endl;
}