#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+7;
struct DSU {
    int rep[N], sz[N];
    vector<int> ops;

    void init() {
        for (int i=0; i<N; i++)
            rep[i] = i, sz[i] = 1;
        ops.clear();
    }

    int find(int u) {
        while(rep[u] != u)  u = rep[u];
        return u;
    }

    bool merge(int u, int v, int x, int &z) {
        u = find(u);
        v = find(v);
        if (u == v)   return false;
        if (sz[u] < sz[v])    swap(u, v);
        rep[v] = u;
        sz[u] += sz[v];
        ops.push_back(v);
        return true;
    }

    void rollback() {
        int u = ops.back();
        sz[rep[u]] -= sz[u];
        rep[u] = u;
        ops.pop_back();
    }
};

