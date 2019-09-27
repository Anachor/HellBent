/// diameter of a tree
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e6 + 100;

int n;
vector<int> G[N];
int far, far_node;
vector<int> dia_nodes;
int diameter;
int st, en;

void dfs1(int u, int p = -1, int d = 1) {
    if(d > far) {
        far = d;
        far_node = u;
    }
    for(int v : G[u]) {
        if(v != p) {
            dfs1(v, u, d + 1);
        }
    }
}
int dfs2(int u, int p = -1) {
    int fl = 0;
    if(u == en) {
        dia_nodes.push_back(u);
        return 1;
    }
    for(int v : G[u]) {
        if(v != p) {
            fl |= dfs2(v, u);
        }
    }
    if(fl) dia_nodes.push_back(u);
    return fl;
}

void find_diameter() {
    dia_nodes.clear();
    far = 0;
    dfs1(1);
    st = far_node;
    far = 0;
    dfs1(st);
    en = far_node;
    diameter = far;
    dfs2(st);
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    find_diameter();
    return 0;
}

