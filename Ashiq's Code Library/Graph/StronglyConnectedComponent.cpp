#include <bits/stdc++.h>
using namespace std;

// 1-based
namespace SCC {
    vector<vector<int>> g, rg, scc, sccg;
    vector<int> nodes, vis, who;
    int comp, n;
    void init(int n_) {
        n = n_;
        g.assign(n+1,{});
        rg.assign(n+1,{});
        vis.assign(n+1,0);
        nodes.clear();
        who.assign(n+1,0);
        comp = 0;
    }
    void addEdge(int u, int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    void dfs1(int u) {
        vis[u] = 1;
        for(int v : g[u]) {
            if(!vis[v]) dfs1(v);
        }
        nodes.push_back(u);
    }
    void dfs2(int u) {
        who[u] = comp;
        for(int v: rg[u]) {
            if (!who[v]) dfs2(v);
        }
    }
    void SCC() {
        for(int i = 1; i <= n; i++) {
            if(!vis[i]) dfs1(i);
        }
        reverse(nodes.begin(), nodes.end());
        for(int u: nodes) {
            if (!who[u]) {
                ++comp;
                dfs2(u);
            }
        }
        scc.assign(comp+1,{});
        for(int i = 1; i <= n; i++) {
            scc[who[i]].push_back(i);
        }
        sccg.assign(comp + 1,{});
        for(int u = 1; u <= n; u++) {
            for(int v : g[u]) {
                if (who[u] != who[v]) {
                    sccg[who[u]].push_back(who[v]);
                }
            }
        }
        for(int i = 1; i <= comp; i++) {
            sort(sccg[i].begin(), sccg[i].end());
            sccg[i].erase(unique(sccg[i].begin(), sccg[i].end()), sccg[i].end());
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    SCC::init(n);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        SCC::addEdge(u, v);
    }
    SCC::SCC();
}
