#include<bits/stdc++.h>
using namespace std;

const int N = 1e6+7;
int n; // number of nodes
vector<int> adj[N]; // adjacency list of graph

bool visited[N];
int tin[N], fup[N];
int timer;

set<pair<int, int> > bridges;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = fup[v] = timer++;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            fup[v] = min(fup[v], tin[to]);
        } else {
            dfs(to, v);
            fup[v] = min(fup[v], fup[to]);
            if (fup[to] > tin[v])
                bridges.insert(make_pair(v, to));
        }
    }
}

void find_bridges() {
    timer = 0;
    memset(visited, 0, sizeof visited);
    memset(tin, -1, sizeof tin);
    memset(fup, -1, sizeof fup);

    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
    }
}
