///Source: Folklore, Anachor

#include<bits/stdc++.h>
using namespace std;

const int N = 3e5+7, K = 20;
vector<int> adj[N];

int anc[N][K];
int level[N];

void setup(int u, int par) {
    level[u] = level[par]+1;
    anc[u][0] = par;
    for (int k=1; k<K; k++)     anc[u][k] = anc[anc[u][k-1]][k-1];

    for (int v: adj[u]) {
        if (v == par)   continue;
        setup(v, u);
    }
}

int lca(int u, int v) {
    if (level[u] > level[v])    swap(u, v);
    for (int k=K-1; k>=0; k--)
        if (level[u] + (1<<k) <= level[v])  v = anc[v][k];

    if (u == v) return u;
    for (int k=K-1; k>=0; k--)
        if (anc[u][k] != anc[v][k])
            u = anc[u][k], v = anc[v][k];
    return anc[u][0];
}

int getanc(int u, int d) {
    for (int k=0; k<K; k++)
        if (d & (1<<k))
            u = anc[u][k];
    return u;
}

int dist(int u, int v) {
    int g = lca(u, v);
    return level[u] + level[v] - 2*level[g];
}



///Given u, v, d per query find dth node (0 indexed) on path from u to v.
///https://codeforces.com/gym/102694/problem/C

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin>>n;

    for (int i=1; i<n; i++) {
        int u, v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    setup(1, 0);

    int q;
    cin>>q;

    while (q--) {
        int u, v, d, ans;
        cin>>u>>v>>d;

        int g = lca(u, v);
        int ll = level[u] - level[g];
        int rr = level[v] - level[g];

        if (d >= ll + rr)   ans = v;
        else if (d <= ll)   ans = getanc(u, d);
        else                ans = getanc(v, ll+rr-d);
        cout<<ans<<"\n";
    }
}
