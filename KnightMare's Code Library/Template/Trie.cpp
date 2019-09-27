#include <bits/stdc++.h>
using namespace std;

const int N=1e6+10;
int tr[N][26];
int pop[N];
int sz=0;

void init()
{
    memset(tr, -1, sizeof tr);
    sz=0;
}

void insert(string &s)
{
    pop[0]++;
    for (int i=0, cur=0; i<s.size(); i++) {
        int c=s[i]-'a';
        if(tr[cur][c] == -1)  tr[cur][c]=++sz;
        cur = tr[cur][c];
        pop[cur]++;
    }
}

int count(string &s)        //Prefix count
{
    int cur=0;
    for (int i=0; i<s.size(); i++) {
        int c=s[i]-'a';
        if(tr[cur][c] == -1)  return 0;
        cur = tr[cur][c];
    }
    return pop[cur];
}

/**
The following code solves SPOJ ADAINDEX
Basically given a list of strings find how
many times a query string appears as prefix.
**/

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin>>n>>m;
    init();
    for (int i=0; i<n; i++)
    {
        string s;
        cin>>s;
        insert(s);
    }

    for (int i=0; i<m; i++)
    {
        string s;
        cin>>s;
        cout<<count(s)<<endl;
    }
}
