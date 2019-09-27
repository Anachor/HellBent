/// cost on Edge , finds max and min
#include <bits/stdc++.h>
using namespace std ;

const int N = 1e5 + 5 , LOG = 20 ;
const long long inf = 1e18 ;

struct LCA {
    vector < pair<int,long long> > G[N] ;
    int par[N][LOG] , depth[N] ;
    long long mx[N][LOG] , mn[N][LOG] ;
    void init() {
        for(int i = 1 ; i < N ; i++) G[i].clear() ;
    }
    void addEdge(int u , int v , long long w) {  /// adds directed edge
        G[u].push_back(make_pair(v,w)) ;
    }
    void lca_init(int root) {
        memset(par,-1,sizeof par) ;
        dfs(root,-1,0,1) ;
    }
    void dfs (int u , int p , long long w , int l) {
        par[u][0] = p ;
        if (u==1) mx[u][0] = -inf , mn[u][0] = inf;
        else mx[u][0] = mn[u][0] = w ;
        depth[u] = l ;
        for (int k = 1 ; k < LOG ; k++) {
            if (par[u][k-1] != -1) {
                par[u][k] = par[par[u][k-1]][k-1];
                mx[u][k] = max(mx[u][k-1],mx[par[u][k-1]][k-1]) ;
                mn[u][k] = min(mn[u][k-1],mn[par[u][k-1]][k-1]) ;
            }
            else {
                mx[u][k] = mx[u][k-1] ;
                mn[u][k] = mn[u][k-1] ;
            }
        }
        for (int i = 0 ; i < G[u].size() ; i++) {
            int v = G[u][i].first ;
            long long w_ = G[u][i].second ;
            if (v != p) {
                dfs(v,u,w_,l+1) ;
            }
        }
    }

    pair<long long,long long> solve (int u , int v) {
        if (depth[u] < depth[v]) {
            swap(u,v) ;
        }
        long long maxi = -inf , mini = inf ;
        int diff = depth[u] - depth[v] ;
        for (int i = LOG-1 ; i >= 0 ; i--) {
            if (diff >= (1<<i)) {
                diff -= (1<<i) ;
                maxi = max(maxi,mx[u][i]) ;
                mini = min(mini,mn[u][i]) ;
                u = par[u][i] ;
            }
        }
        if (u == v) return make_pair(mini,maxi) ;
        for (int i = LOG-1 ; i >= 0 ; i--) {
            if (par[u][i] != par[v][i]) {
                mini = min(mini,mn[u][i]) ;
                maxi = max(maxi,mx[u][i]) ;
                u = par[u][i] ;

                mini = min(mini,mn[v][i]) ;
                maxi = max(maxi,mx[v][i]) ;
                v = par[v][i] ;
            }
        }
        maxi = max(maxi,mx[u][0]) ;
        maxi = max(maxi,mx[v][0]) ;
        mini = min(mini,mn[u][0]) ;
        mini = min(mini,mn[v][0]) ;
        return make_pair(mini,maxi) ;
    }
}Tr;

int main () {
    int tc , caseno = 1;
    cin >> tc ;
    while (tc--) {
        Tr.init() ;
        int n ;
        scanf("%d",&n) ;
        for (int i = 1 ; i < n; i++) {
            int u , v ; long long w ;
            scanf("%d %d %lld",&u , &v , &w) ;
            Tr.addEdge(u,v,w) ;
            Tr.addEdge(v,u,w) ;
        }
        Tr.lca_init(1) ;
        int q ;
        cin >> q ;
        printf ("Case %d:\n",caseno++) ;
        while (q--) {
            int u , v ; scanf("%d %d",&u,&v) ;
            pair<long long,long long> ans = Tr.solve(u,v) ;
            printf ("%lld %lld\n",ans.first,ans.second);
        }
    }
}
