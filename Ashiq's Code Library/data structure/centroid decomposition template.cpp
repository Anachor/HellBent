/// centroid decomposition template

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 100;

vector <int> g[N];
int n;
int child[N];
bool done[N];

void dfs_size(int u, int par) {
    child[u] = 1;
    for (int v: g[u]) {
        if (done[v] or v == par) continue;
        dfs_size(v, u);
        child[u] += child[v];
    }
}

int dfs_find_centroid(int u, int par, int sz) {
    for (int v: g[u]) {
        if (!done[v] and v != par and child[v] > sz) {
            return dfs_find_centroid(v,u,sz);
        }
    }
    return u;
}

void solve (int u) {
    /// problem specific things to do
}


void dfs_decompose(int u) {
    dfs_size(u, -1);
    int centroid = dfs_find_centroid(u, -1, child[u]/2);
    solve(centroid);
    done[centroid] = 1;
    for (int v : g[centroid]) {
        if (!done[v]) dfs_decompose(v);
    }
}


int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs_decompose(1);
}
