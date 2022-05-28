/**
    Hopcroft Karp Bipartite Matching Algorithm
    Complexity: E sqrt(V)   (much better in practice)
    Source: Foreverbell ICPC cheat sheet
    1-indexed. Left and Right independently numbered.
    ml, mr contain matches for left and right parts.

    1. You may pre-calculate a greedy-matching to speed up further
    2. In order to convert to Kuhn remove bfs in matching()
       and (level[u] < level[v]) condition in dfs()


    Source: Folklore, Anachor
*/
#include <bits/stdc++.h>
using namespace std;

namespace HopcroftKarp {
    const int maxN = 1e5+7, maxM = 1e5+7;     ///Check
    int n, m, match;
    int vis[maxN], level[maxN], ml[maxN], mr[maxM];
    vector<int> edge[maxN];   /// constructing edges for left part only

    void init(int N, int M) {      /// N = nodes in left part, M = nodes in right part
        n = N, m = M;
        for (int i=1; i<=n; i++)    edge[i].clear(), ml[i] = -1;
        for (int i=1; i<=m; i++)    mr[i] = -1;
        match = 0;
    }

    void add(int u, int v) {
        edge[u].push_back(v);
        if (ml[u] == -1 && mr[v] == -1)     ml[u] = v, mr[v] = u, match++;
    }

    bool dfs(int u) {
        vis[u] = true;
        for (int x: edge[u]) {
            int v = mr[x];
            if (v == -1 || (!vis[v] && level[u] < level[v] && dfs(v))) {
                ml[u] = x; mr[x] = u;
                return true;
            }
        }
        return false;
    }

    int matching() {
        while (true) {
            queue<int> q;
            for (int i = 1; i <= n; ++i) {
                if (ml[i] == -1)    level[i] = 0, q.push(i);
                else                level[i] = -1;
            }
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int x: edge[u]) {
                    int v = mr[x];
                    if (v != -1 && level[v] < 0) {
                        level[v] = level[u] + 1;
                        q.push(v);
                    }
                }
            }
            for (int i = 1; i <= n; ++i) vis[i] = false;
            int d = 0;
            for (int i = 1; i <= n; ++i) if (ml[i] == -1 && dfs(i)) ++d;
            if (d == 0) return match;
            match += d;
        }
    }
}

/// Solves https://judge.yosupo.jp/problem/bipartitematching

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k;
    cin>>n>>m>>k;

    HopcroftKarp::init(n, m);

    while(k--) {
        int a, b;
        cin>>a>>b;
        a++; b++;
        HopcroftKarp::add(a, b);
    }

    cout<<HopcroftKarp::matching()<<endl;
    for (int i=1; i<=n; i++)
        if (HopcroftKarp::ml[i] != -1)
            cout<<i-1<<" "<<HopcroftKarp::ml[i]-1<<"\n";
}
