/**
Implementation of Dinic's algorithm with optional scaling
Source: Chilli (https://codeforces.com/blog/entry/66006)

Complexity: O(ans*E) or O(V^2E) without scaling, O(VE log(U)) with scaling,
Scaling performs much better in worst case, but has much higher constant factor
To enable scaling, call maxFlow(true)
Everything 0-indexed
*/

#include<bits/stdc++.h>
using namespace std;

namespace Dinic {
    typedef long long LL;
    const int N = 5005, K = 60; /// N > no of nodes, K >= max bits in capacity
    const LL INF = 1e18;

    struct Edge { int frm, to; LL cap, flow; };

    int s, t, n;
    int level[N], ptr[N];
    vector<Edge> edges;
    vector<int> adj[N];

    void init(int nodes) {
        n = nodes;
        for (int i=0; i<n; i++)    adj[i].clear();
        edges.clear();
    }

    /// For adding undirected Edge (u, v, c) call addEdge(u, v, c, c);
    int addEdge(int a, int b, LL cap, LL revcap = 0) {
        edges.push_back({a, b, cap, 0});
        edges.push_back({b, a, revcap, 0});
        adj[a].push_back(edges.size()-2);
        adj[b].push_back(edges.size()-1);
        return edges.size()-2;
    }

    bool bfs(LL lim) {
        fill(level, level+n, -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);

        while (!q.empty() && level[t] == -1) {
            int v = q.front();
            q.pop();
            for (int id: adj[v]) {
                Edge e = edges[id];
                if (level[e.to] == -1 && e.cap - e.flow >= lim) {
                    q.push(e.to);
                    level[e.to] = level[v] + 1;
                }
            }
        }
        return level[t] != -1;
    }
    LL dfs(int v, LL flow) {
        if (v == t || !flow)        return flow;
        for (; ptr[v] < adj[v].size(); ptr[v]++) {
            int eid = adj[v][ptr[v]];
            Edge &e = edges[eid];
            if (level[e.to] != level[v] + 1)    continue;
            if (LL pushed = dfs(e.to, min(flow, e.cap - e.flow))) {
                e.flow += pushed;
                edges[eid^1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
    LL maxFlow(int source, int sink, bool SCALING = false) {
        s = source, t = sink;

        long long flow = 0;
        for (LL lim = SCALING ? (1LL << K) : 1; lim > 0; lim >>= 1) {
            while (bfs(lim)) {
                fill(ptr, ptr+n, 0);
                while (LL pushed = dfs(s, INF)) flow += pushed;
            }
        }
        return flow;
    }

    bool leftOfMinCut(int x) {return level[x] != -1;}

    /// Only works for undirected graph, Make sure to add UNDIRECTED edges. (u, v, c, c)
    /// returns n by n matrix flow, st flow[i][j] = maxFlow
    /// tree holds the edges of a gomory-hu tree of the graph
    vector<vector<LL>> allPairMaxFlow(vector<Edge> &tree) {
        tree.clear();
        vector<vector<LL>> flow(n, vector<LL> (n, INF));

        vector<int> par(n);
        for (int i=1; i<n; i++) {
            for (auto &e: edges)    e.flow = 0;
            LL f = maxFlow(i, par[i]);
            tree.push_back({i, par[i], f});

            for (int j=i+1; j<n; j++)
                if (par[j] == par[i] && leftOfMinCut(j)) par[j] = i;

            flow[i][par[i]] = flow[par[i]][i] = f;
            for (int j=0; j<i; j++)
                if (j != par[i])    flow[i][j] = flow[j][i] = min(f, flow[par[i]][j]);
        }
        return flow;
    }
}

#define ALL_PAIR_FLOW_TEST
#ifndef ALL_PAIR_FLOW_TEST
/// https://www.spoj.com/problems/FASTFLOW/
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin>>n>>m;
    int s = 1, t = n;

    Dinic::init(n+1);
    while (m--) {
        int a, b, c;
        cin>>a>>b>>c;
        Dinic::addEdge(a, b, c, c);
    }
    cout<<Dinic::maxFlow(s, t)<<endl;
}
#else

///AllPair Maxflow test
///Solves https://codeforces.com/gym/101480/problem/J
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin>>n>>m;

    Dinic::init(n);

    for (int i=0; i<m; i++) {
        int u, v;
        cin>>u>>v;
        u--; v--;
        Dinic::addEdge(u, v, 1, 1);
    }

    vector<Dinic::Edge> e;
    auto f = Dinic::allPairMaxFlow(e);

    long long ans = 0;
    for (int i=0; i<n; i++)
        for (int j=i+1; j<n; j++)   ans += f[i][j];
    cout<<ans<<endl;
}
#endif
