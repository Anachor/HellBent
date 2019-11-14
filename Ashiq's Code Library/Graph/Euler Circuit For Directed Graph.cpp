#include <bits/stdc++.h>
using namespace std;

/// Hierholzer's algorithm, finds euler circuit in O(E)

const int N = 1e5 + 100;
vector<int> g[N];
int adj_used[N];
vector<int> circuit;

void euler(int u) {
    while(adj_used[u] < g[u].size()) {
        int v = g[u][adj_used[u]++];
        euler(v);
    }
    circuit.push_back(u);
}

void find_circuit(int n) {
    /// handles self-loop
    for(int i = 1; i <= n; i++) {
        int cnt = 0;
        for(int j = 0; j < adj[i].size(); j++) {
            if(adj[i][j] == i) {
                swap(adj[i][j], adj[i][cnt++]);
            }
        }
    }
    euler(1);
    reverse(circuit.begin(), circuit.end());
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    find_circuit(n);
    return 0;
}

