///Author: anachor

#include<bits/stdc++.h>
using namespace std;

///Everything 0-indexed.
///SCCs are numbered from 0 to cc-1 in topsort order.

namespace SCC {
    const int N = 2e6+7;    ///Check!!!
    vector<int> adj[N], adjr[N];
    vector<int> order;      ///Topsort order
    int which[N];           ///index of SCC which this node belongs to
    int cc;                 ///No of SCCs
    bool vis[N];

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adjr[v].push_back(u);
    }

    void dfs1(int u){
        if (vis[u]) return;
        vis[u] = true;
        for(int v: adj[u]) dfs1(v);
        order.push_back(u);
    }

    void dfs2(int u, int id) {
        if(vis[u]) return;
        vis[u] = true;
        for(int v: adjr[u])  dfs2(v, id);
        which[u] = id;
    }

    int last = 0;
    void findSCC(int n) {
        cc = 0, last = n;
        order.clear();
        fill(vis, vis+n, 0);
        for(int i=0; i<n; i++)
            if(!vis[i])     dfs1(i);
        reverse(order.begin(), order.end());

        fill(vis, vis+n, 0);
        for (int u: order) {
            if (vis[u])     continue;
            dfs2(u, cc);
            ++cc;
        }
    }

    void clear() {
        for (int i=0; i<last; i++)     adj[i].clear(), adjr[i].clear();
    }

}

///If there are n vars x1,....,xn, Node 2*i denotes x_i and 2*i+1 denotes !x_i.
///For example, for clause (x^!y), call OR(2*x, 2*y+1).
///make sure SCC::N >= vars

struct TwoSat {
    int n;
    vector<bool> ans;   ///Solution is stored here
    int vars = 0;

    TwoSat(int n) : n(n), ans(n) {
        SCC::clear();
        vars = 2*n;
    }

    void implies(int x, int y) {
        SCC::addEdge(x, y);
        SCC::addEdge(y^1, x^1);
    }

    void OR(int x, int y) {
        SCC::addEdge(x^1, y);
        SCC::addEdge(y^1, x);
    }

    void XOR(int x, int y) {
        implies(x, y^1);
        implies(x^1, y);
    }

    ///Tested on GYM 101987K
    void atmostOne(vector<int> v) {
        int k = v.size();
        for (int i=0; i<k; i++) {
            if (i+1<k)      implies(vars+2*i, vars+2*i+2);
            implies(v[i], vars+2*i);
            if (i>0)        implies(v[i], vars+2*i-1);
        }
        vars += 2*k;
    }

    bool solve() {
        SCC::findSCC(vars);
        ans.resize(vars/2);
        for (int i=0; i<vars; i+=2) {
            if (SCC::which[i] == SCC::which[i+1])   return false;
            if (i<2*n)      ans[i/2] = SCC::which[i] > SCC::which[i+1];
        }
        return true;
    }
};

///https://judge.yosupo.jp/problem/two_sat
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string s;
    int n, m;
    cin>>s>>s>>n>>m;

    TwoSat solver(n);

    while (m--) {
        int x, y, z;
        cin>>x>>y>>z;
        x = 2*(abs(x)-1)+(x<0);
        y = 2*(abs(y)-1)+(y<0);
        solver.OR(x, y);

    }

    if (false) {
        cout<<"s UNSATISFIABLE"<<endl;
    }
    else {
        cout<<"s SATISFIABLE"<<endl;
        cout<<"v ";
        solver.ans.resize(n);
        for (int i=0; i<solver.ans.size(); i++)    cout<<(solver.ans[i] == 0 ?  -i-1 :i+1)<<" ";
        cout<<0<<endl;
    }
}
