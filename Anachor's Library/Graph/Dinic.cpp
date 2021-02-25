/**
Implementation of Dinic's algorithm with optional scaling
Source: Chilli (https://codeforces.com/blog/entry/66006)

Complexity: O(ans*E) or O(V^2E) without scaling, O(VE log(U)) with scaling,
Scaling performs much better in worst case, but has much higher constant factor
To enable scaling, call maxFlow(true)

*/

#include<bits/stdc++.h>
using namespace std;

namespace Dinic {
    typedef long long LL;
    const int N = 5005, K = 60; /// N > no of nodes, K >= max bits in capacity
    const LL INF = 1e18;

    struct Edge {
        int frm, to;
        LL cap, flow;
    };

    int s, t, n;
    int level[N], ptr[N];
    vector<Edge> edges;
    vector<int> adj[N];

    void init(int nodes, int source, int sink) {
        n = nodes; s = source; t = sink;;
        for (int i=0; i<=n; i++)    adj[i].clear();
        edges.clear();
    }

    int addEdge(int a, int b, LL cap, bool isDirected = true) {
        edges.push_back({a, b, cap, 0});
        edges.push_back({b, a, isDirected ? 0 : cap, 0});
        adj[a].push_back(edges.size()-2);
        adj[b].push_back(edges.size()-1);
        return edges.size()-2;
    }

    bool bfs(LL lim) {
        fill(level, level+n+1, -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;

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
    long long maxFlow(bool SCALING = false) {
        long long flow = 0;
        for (LL lim = SCALING ? (1LL << K) : 1; lim > 0; lim >>= 1) {
            while (bfs(lim)) {
                fill(ptr, ptr+n+1, 0);
                while (LL pushed = dfs(s, INF)) flow += pushed;
            }
        }
        return flow;
    }
}

/// https://www.spoj.com/problems/FASTFLOW/
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin>>n>>m;
    int s = 1, t = n;

    Dinic::init(n+1, s, t);
    while (m--) {
        int a, b, c;
        cin>>a>>b>>c;
        Dinic::addEdge(a, b, c, 0);
//        Dinic::addEdge(b, a, c, 1);
    }
    cout<<Dinic::maxFlow(0)<<endl;
}
