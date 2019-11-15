/*
Given an undirected graph with N vertices's and M edges. You are to process K queries of adding new edges into the graph. After each query you should output the only number - amount of bridges in graph. Graph may contain loops and multiple edges.
*/

#include<bits/stdc++.h>
using namespace std;

const int N = 1e5+7;
int bridges = 0;

struct DSU {
    int par[N], sz[N];

    DSU() {
        for (int i=0; i<N; i++) {
            par[i] = i;
            sz[i] = 1;
        }
    }

    int find(int u) {
        if (par[u] == u)    return u;
        return par[u] = find(par[u]);
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u==v)   return;
        par[v] = u;
        sz[u] += sz[v];
    }
};

DSU rep, root;
int par[N];
list<int>::iterator pos[N];
list<int> adj[N];

void merge(int u) {
    assert(par[u]);
    adj[u].erase(adj[u].begin());
    adj[par[u]].erase(pos[u]);

    for (int v: adj[u]) {
        par[v] = par[u];
        *(adj[v].begin()) = par[u];
    }
    adj[par[u]].splice(adj[par[u]].end(), adj[u]);
    par[u] = 0;
}

void dfs(int u, int p) {
    for (auto it = adj[u].begin(); it != adj[u].end();) {
        if (*it == p)   it = adj[u].erase(it);
        else {
            int v = *it;
            pos[v] = it;
            dfs(v, u);
            it++;
        }
    }
    par[u] = p;
    if (p) {
        adj[u].insert(adj[u].begin(), p);
    }
}

bool takenu[N], takenv[N];

void AddEdge(int u, int v) {
    u = rep.find(u);
    v = rep.find(v);
    if (u == v)     return;

    int ru = root.find(u);
    int rv = root.find(v);

    if (ru == rv) {
        vector<int> au, av;
        int cu = u, cv = v, lca = -1;

        while (true) {
            if (cu) {
                au.push_back(cu);
                takenu[cu] = 1;
            }

            if (cv) {
                av.push_back(cv);
                takenv[cv] = 1;
            }

            if (cu && takenu[cu] && takenv[cu]) {
                lca = cu;
                break;
            }
            if (cv  && takenu[cv] && takenv[cv]) {
                lca = cv;
                break;
            }
            cu = par[cu];
            cv = par[cv];
        }

        assert(lca > 0);

        for (int x: au) {
            if (x == lca)   break;
            bridges--;
            merge(x);
            rep.merge(lca, x);
        }

        for (int x: av) {
            if (x == lca)   break;
            bridges--;
            merge(x);
            rep.merge(lca, x);
        }

        for (int x: au)     takenu[x] = false;
        for (int x: av)     takenv[x] = false;

    }
    else {
        if (root.sz[ru] < root.sz[rv]) {
            swap(ru, rv);
            swap(u, v);
        }

        dfs(v, 0);
        assert(par[v] == 0);

        pos[v] = adj[u].insert(adj[u].end(), v);
        par[v] = u;
        adj[v].insert(adj[v].begin(), u);
        root.merge(u, v);
        bridges++;
    }
//
//    for (int i=1; i<=4; i++) {
//        cout<<i<<"----> par: "<<par[i]<<", rep: "<<rep.find(i)<<", root: "<<root.find(i);
//        if (par[i]) cout<<", pos"<<": "<<distance(adj[par[i]].begin(), pos[i]);
//        cout<<endl;
//
//        for (auto it = adj[i].begin(); it != adj[i].end(); it++) {
//            cout << "::: "<< distance(adj[i].begin(), it) << ": " << (*it) << endl;
//        }
//    }
}

int main() {
    freopen("bridges.in", "r", stdin);
    freopen("bridges.out", "w", stdout);

    int n, m;
    cin>>n>>m;

    for (int i=1; i<=m; i++) {
        int u, v;
        cin>>u>>v;
        AddEdge(u, v);
    }

    int q;
    cin>>q;
    for (int i=1; i<=q; i++) {
        int u, v;
        cin>>u>>v;
        AddEdge(u, v);
        cout<<bridges<<"\n";
    }
}
