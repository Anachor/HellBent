/**
 Adjacency list implementation of Edmonds-Karp algorithm.
 For Undirected graphs, add the commented line in AddEdge.
 Source : Emaxx (modified)

 Running time:  O(VE^2)
 Memory: O(V^2)
 
 INPUT:
     - graph, constructed using AddEdge()
     - source and sink

 OUTPUT:
     - maximum flow value
     - To obtain actual flow values, either keep an extra matrix,
       or save a copy of the original capacity matrix and subtract
**/

#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, LL> PIL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<VL> VVL;

const LL INF = 1e18+7;

struct EdmondsKarp
{
    int n;
    VVL cap;
    VVI adj;

    EdmondsKarp(int nn) {
        n = nn;
        cap = VVL(n,  VL(n));
        adj = VVI(n);
    }

    void AddEdge(int u, int v, LL c) {
        if (u==v)   return;
        adj[u].push_back(v);
        adj[v].push_back(u);
        cap[u][v] += c;
        ///cap[v][u] += c;      // For Undirected Graphs.
    }

    LL bfs(int s, int t) {
        VI par(n, -1);
        par[s] = -2;
        queue<PIL> q;
        q.push({s, INF});
        LL ans = 0;

        while (!q.empty()) {
            int u = q.front().first;
            LL flow = q.front().second;
            q.pop();

            for (int v : adj[u]) {
                if (par[v] == -1 && cap[u][v]) {
                    par[v] = u;
                    LL new_flow = min(flow, cap[u][v]);
                    if (v == t) {ans = new_flow; break;}
                    q.push({v, new_flow});
                }
            }
        }

        if (ans == 0)   return 0;
        int cur = t;
        while (cur != s) {
            int prev = par[cur];
            cap[prev][cur] -= ans;
            cap[cur][prev] += ans;
            cur = prev;
        }
        return ans;
    }

    LL MaxFlow(int s, int t) {
        LL flow = 0;
        while (LL new_flow = bfs(s, t))
            flow += new_flow;
        return flow;
    }
};

///Solves SPOJ MTOTALF - Total Flow
///Given a graph find the max flow between two nodes
int main()
{
    int m;
    cin>>m;

    EdmondsKarp solver(130);
    for (int i=0; i<m; i++) {
        char u, v;
        int cap;
        cin>>u>>v>>cap;
        solver.AddEdge(u, v, cap);
    }

    cout<<solver.MaxFlow('A', 'Z')<<endl;
}
