#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5 , LOG = 20 ;
int par[N][LOG] , depth[N] ;
vector <int> g[N] ;

void dfs (int u , int p , int lvl) {
    par[u][0] = p ;
    depth[u] = lvl ;
    for (int i = 0 ; i < g[u].size() ; i++) {
        int v = g[u][i] ;
        if (v == p) continue ;
        dfs (v,u,lvl+1) ;
    }
}


void init(int root , int n) {
    dfs(root,-1,1) ;
    for (int k = 1 ; k < LOG ;k++) {
        for (int i = 1 ; i <= n ; i++) {
            if (par[i][k-1] != -1)
                par[i][k] = par[par[i][k-1]][k-1] ;
            else
                par[i][k] = -1 ;
        }
    }
}


int lca (int u , int v) {
    if (depth[u] < depth[v]) {  /// u nichey
        swap(u,v) ;
    }
    int diff = depth[u] - depth[v] ;
    for (int i = LOG-1 ; i >= 0 ; i--) {
        if (diff >= (1<<i)) {
            diff -= (1<<i) ;
            u = par[u][i] ;
        }
    }
    if (u == v) return u ;
    for (int i = LOG-1 ; i >= 0 ; i--) {
        if (par[u][i] != par[v][i]) {
            u = par[u][i] ;
            v = par[v][i] ;
        }
    }
    return par[v][0] ;
}

int kth_par(int u , int k) {
    for (int i = LOG-1 ; i >= 0 ; i--) {
        if (k >= (1<<i)) {
            k -= (1<<i) ;
            u = par[u][i] ;
        }
        if (u == -1) return u ;
    }
    return u ;
}


int main () {

    return 0 ;
}
