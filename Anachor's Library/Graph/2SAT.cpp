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

    void clear() {
        for (int i=0; i<N; i++)     adj[i].clear(), adjr[i].clear();
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adjr[v].push_back(u);
        order.clear();
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

    void findSCC(int n) {
        cc = 0;

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
}

///If there are n vars x1,....,xn, Node 2*i denotes x_i and 2*i+1 deonotes !x_i.
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
        implies(x^1, y);
    }

    void XOR(int x, int y) {
        implies(x, !y);
        implies(!x, y);
    }

    void forceTrue(int x, bool val) {
        SCC::addEdge(x^1, x);
    }

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
        for (int i=0; i<vars; i+=2) {
            if (SCC::which[i] == SCC::which[i+1])
                return false;
            if (i<2*n)      ans[i/2] = SCC::which[i] > SCC::which[i+1];
        }
        return true;
    }
};

///solves CF 1215F
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, p, M, m;
    cin>>n>>p>>M>>m;

    TwoSat solver(p+M+1);

    for (int i=0; i<n; i++) {
        int x, y;
        cin>>x>>y;
        x--; y--;
        solver.OR(2*x, 2*y);
    }

    for (int i=0; i<p; i++) {
        int l, r;
        cin>>l>>r;
        solver.implies(2*i, 2*(p+r));
        solver.implies(2*i, 2*(p+l-1)+1);
    }

    for (int i=0; i<M; i++) {
        solver.implies(2*(p+i), 2*(p+i+1));
    }

    for (int i=0; i<m; i++) {
        int x, y;
        cin>>x>>y;
        x--; y--;
        solver.OR(2*x+1, 2*y+1);
    }

    bool b = solver.solve();
    if (!b) {
        cout<<-1<<endl;
        return 0;
    }

    vector<int> ans;
    for (int i=0; i<p; i++)
        if (solver.ans[i])
            ans.push_back(i+1);

    int f;
    for (int i=1; i<=M; i++)
        if (solver.ans[p+i]) {
            f = i;
            break;
        }
    cout<<ans.size()<<" "<<f<<endl;
    for (int x: ans)    cout<<x<<" ";
}
