/**
 Adjacency list implementation of Ford-Fulkerson algorithm.
 For Undirected graphs, add each edge in both directions

 Running time:  O(E * flow)
 Memory : O(V+E)

 INPUT:
     - graph, constructed using AddEdge()
     - source and sink

 OUTPUT:
     - maximum flow value
     - To obtain actual flow values, look at edges with capacity > 0
       (zero capacity edges are residual edges).
**/

#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef vector<int> VI;
typedef vector<VI> VVI;
const LL INF = 1e18+7;

struct Edge {
  int u, v;
  LL cap, flow;
  Edge() {}
  Edge(int u, int v, LL cap): u(u), v(v), cap(cap), flow(0) {}
};

struct FordFulkerson
{
    int n;
    VVI adj;
    vector<Edge> edges;
    vector<bool> vis;

    FordFulkerson(int nn) {
        n = nn;
        adj = vector<VI> (n);
        vis = vector<bool> (n);
    }

    void AddEdge(int u, int v, LL c) {
        if (u==v)   return;
        edges.emplace_back(u, v, c);
        adj[u].emplace_back(edges.size() - 1);
        edges.emplace_back(v, u, 0);
        adj[v].emplace_back(edges.size() - 1);
    }

    LL dfs(int u, int t, LL flow=INF) {
        if (u==t)   return flow;
        vis[u] = 1;

        for (int i: adj[u]) {
            Edge &e = edges[i];
            Edge &oe = edges[i^1];
            if (!vis[e.v] && e.cap > e.flow) {
                LL cur = min(flow, e.cap-e.flow);
                LL newflow = dfs(e.v, t, cur);
                if (newflow == 0)   continue;
                e.flow  += newflow;
                oe.flow -= newflow;
                return newflow;
            }
        }
        return 0;
    }

    LL MaxFlow(int s, int t) {
        LL flow = 0;
        while (true) {
            fill(vis.begin(), vis.end(), 0);
            LL new_flow = dfs(s, t);
            if (new_flow == 0)  break;
            flow += new_flow;
        }
        return flow;
    }
};

///Solves SPOJ MTOTALF - Total Flow
///Given a graph find the max flow between two nodes
int main()
{
    int m;
    cin>>m;

    FordFulkerson solver(130);
    for (int i=0; i<m; i++) {
        char u, v;
        int cap;
        cin>>u>>v>>cap;
        solver.AddEdge(u, v, cap);
    }
    cout<<solver.MaxFlow('A', 'Z')<<endl;;
}
