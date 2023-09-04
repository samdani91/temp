#include<bits/stdc++.h>
using namespace std;

typedef  long long int          ll;
typedef  long double            ld;
typedef  string                 str;
typedef  vector<ll>             vll;
typedef  vector<string>         vs;
typedef  vector<pair<ll, ll>>   vpl;
typedef  set<ll>                sll;
typedef  map<ll,ll>             mll;
typedef  pair<int,int>          pint;
typedef  pair<ll,ll>            pll;
double   pi = acos(-1.0);
#define  debug(x)              cerr<<#x<< <<x<<endl;
#define  loop                   for(ll i=1; i<=n; i++)
#define  all(a)                 (a).begin(), (a).end()
#define  min3(a,b,c)            min(a,min(b,c))
#define  max3(a,b,c)            max(a,max(b,c))
#define  min4(a,b,c,d)          min(a,min(b,min(c,d)));
#define  max4(a,b,c,d)          max(a,max(b,max(c,d)));

int main()
{
    int q,a,x;
    cin>>q;
    set<int>st;
    set<int>::iterator it;
    while(q--){
        cin>>a>>x;
        it=st.find(x);
        if(a==1) st.insert(x);
        else if(a==2 && it!=st.end()) st.erase(x);
        else if(a==3 && it!=st.end()) {
            cout<<"Yes"<<endl;
        }
        else if(a==3 && it==st.end()) cout<<"No"<<endl;

    }
    

    return 0;
}