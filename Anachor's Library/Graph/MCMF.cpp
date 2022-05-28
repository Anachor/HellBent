/**
Min Cost Max Flow Using Successive Shortest Path
Complexity: SPFA: O(ans*VE) ,
    Dijkstra: O(ans*ElogV) + Cost of Normalization
    Normalization:  Sets potentials (pi) for Dijkstra()
        If all edges >= 0: you may comment out normalize()
        If graph is DAG, use DP in O(m)
        Otherwise, SPFA() is used in O(mn)

Author: anachor
**/
#include<bits/stdc++.h>
using namespace std;


namespace MCMF {
    typedef long long F; typedef long long C;
    const F infF = 1e18; const C infC = 1e18;

    const int N = 5005;
    typedef pair<C, F> PCF;

    struct Edge {int frm, to; C cost; F cap, flow;};

    int n, s, t;
    vector<Edge> edges;
    vector<int> adj[N];
    C pi[N], dis[N];
    F fl[N];
    int prv[N], vis[N];

    void init(int nodes, int source, int sink) {
        n = nodes, s = source, t = sink;
        for (int i=0; i<n; i++) pi[i] = 0, adj[i].clear();
        edges.clear();
    }

    void addEdge(int u, int v, F cap,C cost) {
        edges.push_back({u, v, cost, cap, 0});
        edges.push_back({v, u, -cost, 0, 0});
        adj[u].push_back(edges.size()-2);
        adj[v].push_back(edges.size()-1);
    }

    bool SPFA() {
        for (int i=0; i<n; i++) {
            dis[i] = infC; fl[i] = 0;
            vis[i] = 0; prv[i] = -1;
        }
        queue<int> q;
        q.push(s);
        dis[s] = 0; fl[s] = infF; vis[s] = 1;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            vis[u] = 0;
            for (int eid : adj[u]) {
                Edge &e = edges[eid];
                if (e.cap == e.flow) continue;

                if (dis[u] + e.cost < dis[e.to]) {
                    dis[e.to] = dis[u] + e.cost;
                    fl[e.to] = min(fl[u], e.cap - e.flow);
                    prv[e.to] = eid^1;
                    if (!vis[e.to])     q.push(e.to);
                }
            }
        }
        return fl[t] > 0;
    }

    PCF solveSPFA() {
        C cost = 0; F flow = 0;
        while (SPFA()) {
            C pathcost = dis[t];
            cost += pathcost*fl[t]; flow += fl[t];
            for (int u=t, e=prv[u]; e!=-1; u=edges[e].to, e=prv[u]) {
                edges[e].flow -= fl[t];
                edges[e^1].flow += fl[t];
            }
        }
        return {cost, flow};
    }

    void normalize() {
        SPFA();
        for (int i=0; i<n; i++) pi[i] = dis[i];
    }

    bool Dijkstra() {
        for (int i=0; i<n; i++) {
            dis[i] = infC; fl[i] = 0;
            vis[i] = 0; prv[i] = -1;
        }
        priority_queue<pair<C, int>> pq;
        pq.emplace(0, s);
        dis[s] = 0; fl[s] = infF;

        while (!pq.empty()) {
            int u = pq.top().second; pq.pop();
            if (vis[u]) continue;
            vis[u] = 1;

            for (int eid : adj[u]) {
                Edge &e = edges[eid];
                if (vis[e.to] || e.cap == e.flow) continue;

                C nw = dis[u] + e.cost - pi[e.to] + pi[u];
                if (nw < dis[e.to]) {
                    dis[e.to] = nw;
                    fl[e.to] = min(fl[u], e.cap - e.flow);
                    prv[e.to] = eid^1;
                    pq.emplace(-dis[e.to], e.to);
                }
            }
        }
        return fl[t] > 0;
    }

    PCF solveDijkstra() {
        normalize();
        C cost = 0; F flow = 0;
        while (Dijkstra()) {
            for (int i=0; i<n; i++)
                if (fl[i])     pi[i] += dis[i];
            C pathcost = pi[t]-pi[s];
            cost += pathcost*fl[t]; flow += fl[t];

            for (int u=t, e=prv[u]; e!=-1; u=edges[e].to, e=prv[u]) {
                edges[e].flow -= fl[t];
                edges[e^1].flow += fl[t];
            }
        }
        return {cost, flow};
    }
}

/// More tests: https://docs.google.com/spreadsheets/d/1NMolWZsOU5mUIYr31PCs2IpvciFTko3vmrydzutpWhg/edit?usp=sharing
/// https://open.kattis.com/problems/mincostmaxflow
int main(){
    int n, m, s, t;
    cin>>n>>m>>s>>t;

    MCMF::init(n+1, s, t);

    for (int i=0; i<m; i++) {
        int a, b, c, w;
        cin>>a>>b>>c>>w;
        MCMF::addEdge(a, b, c, w);
    }

    auto [c, f] = MCMF::solveDijkstra();
    cout<<f<<" "<<c<<endl;
}

