#include <bits/stdc++.h>
using namespace std;
#define mx 100

map<string, int> names;
int vertex;
int edges;
int dis[mx];
int graph[mx][mx] = {0};
int D[mx][mx]={0};
int P[mx][mx]={0};


void read();
void printGraph(int G[][mx]);
void floyd_warshall();
void printPath(int s,int d);



int main()
{
    string dest;
    read();
    //printGraph(graph);

    for(int i=1;i<=vertex;i++){
        for(int j=1;j<=vertex;j++){
            if(i==j || graph[i][j]==INT32_MAX) P[i][j]=INT32_MAX;
            else if(i!=j && graph[i][j]<INT32_MAX) P[i][j]=i;
        }
    }
    floyd_warshall();
    // printPath(5,1);
    // cout<<1<<endl;
    return 0;
}

void read()
{   
    freopen("input.txt", "r", stdin);
    string s;
    cin>>vertex>>edges;
    int w, x, y, i = 0;
    
    while (edges--)
    {
        
        cin>>s;
        
        if (names[s] == 0)
        {
            names[s] = ++i;
        }
        x = names[s];
        cin >> s;
        if (names[s] == 0)
        {
            names[s] = ++i;
        }
        y = names[s];
        cin >> w;
        graph[x][y] = w;
    }

    for (int i = 1; i <= names.size(); i++)
    {
        for (int j = 1; j <= names.size(); j++)
        {   
            if(i!=j && graph[i][j]==0) graph[i][j]=INT32_MAX;
        }
    }
}

void floyd_warshall()
{
    for (int i = 1; i <= names.size(); i++)
    {
        for (int j = 1; j <= names.size(); j++)
        {   
            D[i][j]=graph[i][j];
        }
    }
    printGraph(D);
    for(int k=1;k<=names.size();k++){
        for(int i=1;i<=names.size();i++){
            for(int j=1;j<=names.size();j++){
                if(D[i][k] + D[k][j] < D[i][j]){
                    D[i][j]=D[i][k] + D[k][j];
                    P[i][j]=P[k][j];
                }
            }
        }
    }
    printGraph(P);
    
}
void printGraph(int G[][mx])
{
    for (int i = 1; i <= names.size(); i++)
    {
        for (int j = 1; j <= names.size(); j++)
        {   
            cout << G[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl<<endl<<endl;;
}

void printPath(int s,int d)
{
    if (P[s][d]== INT32_MAX){
        cout<<"No Path"<<endl;
        return;
    }
    else if(P[s][d]==s){
        for (auto x : names)
        {
            if (x.second == s)
            {
                cout << x.first << " ";
                break;
            }
        }
    }
    else{
        printPath(s,P[s][d]);
        printPath(P[s][d],d);
    }
    
}