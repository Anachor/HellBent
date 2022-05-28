//Source: Zawad


#include<bits/stdc++.h>
using namespace std;
typedef vector<int> VI;
typedef vector<VI> VVI;

///1-indexed
struct ChudirBhai {
    int n, T;
    VVI g, tree, rg, bucket;
    VI sdom, par, dom, dsu, label, arr, rev;

    ChudirBhai(int n): n(n), g(n+1), tree(n+1), rg(n+1), bucket(n+1),
                       sdom(n+1), par(n+1), dom(n+1), dsu(n+1), label(n+1),
                       arr(n+1), rev(n+1), T(0) {
        for(int i = 1; i <= n; i++) sdom[i] = dom[i] = dsu[i] = label[i] = i;
    }

    void addEdge(int u, int v) { g[u].push_back(v); }

    void dfs0(int u) {
        T++; arr[u] = T, rev[T] = u;
        label[T] = T, sdom[T] = T, dsu[T] = T;

        for(int i = 0; i < g[u].size(); i++) {
            int w = g[u][i];
            if(!arr[w]) dfs0(w), par[arr[w]] = arr[u];
            rg[arr[w]].push_back(arr[u]);
        }
    }

    int Find(int u, int x = 0) {
        if(u == dsu[u]) return x? -1: u;
        int v = Find(dsu[u], x+1);
        if(v < 0) return u;
        if(sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
        dsu[u] = v;
        return x? v: label[u];
    }

    void Union(int u, int v) { dsu[v] = u; }

    VVI buildAndGetTree(int s) {
        dfs0(s);
        for(int i = n; i >= 1; i--) {
            for(int j = 0; j < rg[i].size(); j++)
                sdom[i] = min(sdom[i], sdom[Find(rg[i][j])]);
            if(i > 1) bucket[sdom[i]].push_back(i);

            for(int j = 0; j < bucket[i].size(); j++) {
                int w = bucket[i][j], v = Find(w);
                if(sdom[v] == sdom[w]) dom[w] = sdom[w];
                else dom[w] = v;
            }
            if(i > 1) Union(par[i], i);
        }

        for(int i = 2; i <= n; i++) {
            if(dom[i] != sdom[i]) dom[i] = dom[dom[i]];
            tree[rev[i]].push_back(rev[dom[i]]);
            tree[rev[dom[i]]].push_back(rev[i]);
        }
        return tree;
    }

    ///Idom(u) = 0 if u is unreachable, IDom(root) = root;
    int getIDom(int u) {
        return rev[dom[arr[u]]];
    }
};
///Solves https://codeforces.com/gym/100513/problem/L

const int N = 2e5+7;
VVI adj;
int st[N], en[N], tt = 0;
void dfs(int u, int p) {
    st[u] = ++tt;
    for (int v: adj[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    en[u] = tt;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    while (cin>>n>>m) {
        ChudirBhai solver(n);

        vector<pair<int, int>> edges;
        for (int i=0; i<m; i++) {
            int u, v;
            cin>>u>>v;
            solver.addEdge(u, v);
            edges.push_back({u, v});
        }

        adj = solver.buildAndGetTree(1);
        dfs(1, -1);

        for (int i=1; i<=n; i++)    cout<<i<<" "<<solver.getIDom(i)<<endl;

        vector<int> ans;
        for (int i=0; i<edges.size(); i++) {
            int u = edges[i].first, v = edges[i].second;
            if (u > 1 && solver.getIDom(u) == 0)   continue;
            if (!(st[v] <= st[u] && en[u] <= en[v]))   ans.push_back(i+1);
        }
        cout<<ans.size()<<"\n";
        for (int x: ans)    cout<<x<<" ";
        cout<<"\n";
    }
}
