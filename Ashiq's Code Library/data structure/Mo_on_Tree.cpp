/* Bubble Cup X - Finals [ Online Mirror ] */
/* I - Dating */
/* Mo on trees */

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5 , BLOCK = 320 , LOG = 20;
int n , a[N] , taken[N] , node[N] , depth[N] , mof[N] , f[N] , st[N] , en[N] , par[N][LOG] ;
long long res[N] , cnt[N][2] , ans ;
vector <int> g[N] ;
int Timer = 0 ;
struct Query {
    int u , v , id , l , r;
    bool operator <(const Query &p) const{
		int a = l/BLOCK, b = p.l/BLOCK;
		return a == b ? r < p.r : a < b;
	}
}Q[N];

void dfs (int u , int p , int lvl) {
    par[u][0] = p ;
    depth[u] = lvl ;
    st[u] = ++Timer ;
    node[Timer] = u ;
    for (auto v:g[u]) {
        if (v == p) continue ;
        dfs(v,u,lvl+1) ;
    }
    en[u] = ++Timer ;
    node[Timer] = u ;
}

void init(int n) {
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
    if (depth[u] < depth[v]) {
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



int compress() {
    vector <int> v ; map<int,int> Map ;
    for (int i = 1 ; i <= n ; i++) {
        v.push_back(f[i]) ;
    }
    sort (v.begin(),v.end()) ;
    v.erase(unique(v.begin(),v.end()),v.end()) ;
    for (int i = 0 ; i < v.size() ; i++) {
        Map[v[i]] = i+1 ;
    }
    for (int i = 1 ; i <= n ; i++) {
        f[i] = Map[f[i]] ;
    }
    return (int)v.size() ;
}

void add (int t) {
    int u = node[t] ;
    if (taken[u]) {
        cnt[f[u]][mof[u]]-- ;
        ans -= cnt[f[u]][mof[u]^1] ;
    }
    else {
        cnt[f[u]][mof[u]]++;
        ans += cnt[f[u]][mof[u]^1] ;
    }
    taken[u] ^= 1 ;
}

/// del function lage na
void del (int t) {
    int u = node[t] ;
    if (taken[u]) {
        cnt[f[u]][mof[u]]-- ;
        ans -= cnt[f[u]][mof[u]^1] ;
    }
    else {
        cnt[f[u]][mof[u]]++ ;
        ans += cnt[f[u]][mof[u]^1] ;
    }
    taken[u] ^= 1 ;
}
int main () {
   // freopen ("in.txt" , "r" , stdin) ;
    scanf ("%d" , &n) ;
    for (int i = 1 ; i <= n ; i++) {
        scanf ("%d" , &mof[i]) ;
    }
    for (int i = 1 ; i <= n ; i++) {
        scanf ("%d" , &f[i]) ;
    }
    compress() ;
    for (int i = 1 ; i < n ; i++) {
        int u , v ;
        scanf ("%d %d" , &u , &v) ;
        g[u].push_back(v) ; g[v].push_back(u) ;
    }
    dfs(1,-1,1) ;
    init(n) ;
    int q ; scanf ("%d" , &q) ;
    for (int i = 1 ; i <= q; i++) {
        int u , v ;
        scanf ("%d %d" , &u , &v) ;
        if (st[u] > st[v]) swap(u,v) ;
        if (st[u] <= st[v] and en[u] >= en[v]) {
            Q[i] = {u,v,i,st[u],st[v]} ;
        }
        else {
            Q[i] = {u,v,i,en[u],st[v]} ;
        }
    }
    sort (Q+1,Q+q+1) ;
    int L = 1 , R = 0 ;
    for (int i = 1 ; i <= q ; i++) {
        int u = Q[i].u , v = Q[i].v ;
        int ql = Q[i].l , qr = Q[i].r  ;
        while (L < ql) del(L++) ;
        while (L > ql) add(--L) ;
        while (R > qr) del(R--) ;
        while (R < qr) add(++R) ;
        int anc = lca(u,v) ;
        res[Q[i].id] = ans ;
        if (anc != u and anc != v) {
            res[Q[i].id] += cnt[f[anc]][mof[anc]^1] ;
        }
    }
    for (int i = 1 ; i <= q ; i++) {
        printf ("%lld\n" , res[i]) ;
    }
    return 0 ;
}

