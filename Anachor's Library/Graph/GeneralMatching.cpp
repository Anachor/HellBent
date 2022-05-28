/// General Graph Matching (Gabow-Edmonds)
/// Source: Arghya Da
/// Complexity: O(n m log n)
/// Input: Graph constructed with AddEdge (1-indexed)
/// Output: max no of match. match[i] contains partner
/// Calculate greedy pre-matching for improvement

#include <bits/stdc++.h>
using namespace std;

namespace Blossom   {
    const int N = 5005;
    int vis[N], par[N], orig[N], match[N], aux[N];
    int t, n, ans;
    vector<int> adj[N];
    queue<int> q;
    void init(int nn) {
        n = nn; t = ans = 0;
        for(int i=0; i<=n; i++) {
            adj[i].clear();
            match[i] = aux[i] = par[i] = 0;
        }
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        if (!match[u] && !match[v]) {
            match[u] = v;
            match[v] = u;
            ans++;
        }
    }
    void augment(int u, int v) {
        int pv = v, nv;
        do {
            pv = par[v];
            nv = match[pv];
            match[v] = pv;
            match[pv] = v;
            v = nv;
        }
        while(u != pv);
    }

    int lca(int v, int w) {
        ++t;
        while(true) {
            if(v) {
                if(aux[v] == t) return v;
                aux[v] = t;
                v = orig[par[match[v]]];
            }
            swap(v, w);
        }
    }
    void blossom(int v, int w, int a) {
        while(orig[v] != a) {
            par[v] = w;
            w = match[v];
            if(vis[w] == 1) q.push(w), vis[w] = 0;
            orig[v] = orig[w] = a;
            v = par[w];
        }
    }
    bool bfs(int u) {
        fill(vis+1, vis+1+n, -1);
        iota(orig+1, orig+n+1, 1);
        q = queue<int> ({u});
        vis[u] = 0;
        while(!q.empty()) {
            int v = q.front(); q.pop();
            for(int x: adj[v]) {
                if(vis[x] == -1) {
                    par[x] = v;
                    vis[x] = 1;
                    if(!match[x]) {
                        augment(u, x);
                        return true;
                    }
                    q.push(match[x]);
                    vis[match[x]] = 0;
                }
                else if(vis[x] == 0 && orig[v] != orig[x]) {
                    int a = lca(orig[v], orig[x]);
                    blossom(x, v, a);
                    blossom(v, x, a);
                }
            }
        }
        return false;
    }
    int maxMatching() {
        for(int i=1; i<=n; ++i) if(!match[i] && bfs(i)) ++ans;
        return ans;
    }
}

///More problems: SPOJ ADABLOOM

/// Solves https://judge.yosupo.jp/problem/general_matching
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin>>n>>m;

    Blossom::init(n);
    while (m--) {
        int u, v;
        cin>>u>>v;
        u++;v++;
        Blossom::addEdge(u, v);
    }
    cout<<Blossom::maxMatching()<<endl;

    for (int i=1; i<=n; i++)
        if (Blossom::match[i] && Blossom::match[i] < i) cout<<Blossom::match[i]-1<<" "<<i-1<<"\n";
}
