/// Dominator Tree
#include <bits/stdc++.h>
using namespace std ;
#define mp make_pair
const int N = 1e5 + 5 , M = 5e5 + 5 , inf = 1e9 , LOG = 17 ;
int n , m ; // # of nodes and edges
vector < pair<int,int> > adj[N] ; // stores main graph
int a[M] , b[M] , W[M] ; // stores main graph
int dist[N] ; // distance calculated with dijkstra

vector <int> dag[N] ; // stores the DAG
vector <int> reverseDag[N] ; // stores reverse of DAG
stack <int> sorted ; // nodes in topSorted order of DAG
int vis[N] ; // used to topSort the nodes in DAG

vector <int> g[N] ; // stores dominator tree /// keeps edges in both way
int parent[N][LOG] ; // parents for dominator tree
int depth[N] ; // level of domiantor tree

int subTree[N] ;

void dijkstra (int src) {
    for (int i = 0 ; i <= n ; i++) {
        dist[i] = inf ;
    }
    dist[src] = 0 ;
    priority_queue < pair<int,int> > pq ;
    pq.push(mp(0,src)) ;
    while (!pq.empty()) {
        int u = pq.top().second ;
        int cost = -pq.top().first ;
        pq.pop() ;
        if (dist[u] < cost) {
            continue ;
        }
        for (int i = 0 ; i < adj[u].size() ; i++) {
            int v = adj[u][i].first , w = adj[u][i].second ;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w ;
                pq.push(mp(-dist[v],v)) ;
            }
        }
    }
}

void makeDag() {
    for (int i = 0 ; i <= n ; i++) {
        dag[i].clear() ;
        reverseDag[i].clear() ;
    }
    for (int i = 1 ; i <= m ; i++) {
        int u = a[i] , v = b[i] , w = W[i];
        if (dist[u] >= inf) continue ; // handles disconnected graph
        if (dist[u] + w == dist[v]) {
            dag[u].push_back(v) ;
            reverseDag[v].push_back(u) ;
        }
        else if (dist[v] + w == dist[u]) {
            dag[v].push_back(u) ;
            reverseDag[u].push_back(v) ;
        }
    }
}

void dfs (int u) {
    vis[u] = 1 ;
    for (int i = 0 ; i < dag[u].size() ; i++) {
        int v = dag[u][i] ;
        if (!vis[v]) {
            dfs(v) ;
        }
    }
    sorted.push(u) ;
}

void topSort () {
    memset (vis , 0 , sizeof vis) ;
    while (!sorted.empty()) sorted.pop() ;
    for (int i = 1 ; i <= n ; i++) {
        if (dist[i] >= inf) continue; // handles disconnected graph
        if (!vis[i]) {
            dfs(i) ;
        }
    }
}


int LCA (int u , int v) {
    if (depth[u] < depth[v]) {  // u nichey
        swap(u,v) ;
    }
    int diff = depth[u] - depth[v] ;
    for (int i = LOG-1 ; i >= 0 ; i--) {
        if (diff >= (1<<i)) {
            diff -= (1<<i) ;
            u = parent[u][i] ;
        }
    }
    if (u == v) return u ;
    for (int i = LOG-1 ; i >= 0 ; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i] ;
            v = parent[v][i] ;
        }
    }
    return parent[v][0] ;
}


void dominator (int src) {
    for (int i = 0 ; i <= n ; i++) {
        for (int k = 0 ; k < LOG ; k++) {
            parent[i][k] = -1 ;
        }
    }
    for (int i = 0 ; i <= n ; i++) {
        g[i].clear() ;
    }
    while (!sorted.empty()) {
        int u = sorted.top() ;
        sorted.pop() ;
        if (u == src) {
            continue ;
        }
        int par = reverseDag[u].back() ;
        for (int i = 0 ; i < reverseDag[u].size() ; i++) {
            int v = reverseDag[u][i] ;
            par = LCA(par,v) ;
        }
        g[u].push_back(par) ;
        g[par].push_back(u) ;
        parent[u][0] = par ;
        depth[u] = depth[par] + 1 ;
        for (int k = 1 ; k < LOG ; k++) {
            if (parent[u][k-1] == -1) {
                break ;
            }
            parent[u][k] = parent[parent[u][k-1]][k-1] ;
        }
    }
}

void solve (int u , int p) {
    subTree[u] = 1 ;
    for (int i = 0 ;i < g[u].size() ; i++) {
        int v = g[u][i] ;
        if (v == p) continue ;
        solve(v , u) ;
        subTree[u] += subTree[v] ;
    }
}

int src = 1 ;

int main () {
    //freopen ("in.txt", "r", stdin) ;
    int tc , caseno = 1 ;
    scanf ("%d" , &tc) ;
    while (tc--) {
        scanf ("%d %d" , &n , &m) ;
        for (int i = 0 ; i <= n ; i++) {
            adj[i].clear() ;
        }
        for (int i = 1 ; i <= m ; i++) {
            int u , v , w ;
            scanf ("%d %d %d" , &u , &v , &w) ;
            a[i] = ++u , b[i] = ++v , W[i] = w ;
            adj[u].push_back(mp(v,w)) ;
            adj[v].push_back(mp(u,w)) ;
        }
        dijkstra(src) ;
        makeDag() ;

        topSort() ;
        dominator(src) ;
        solve(src,-1) ;
        printf ("Case %d:\n" , caseno++) ;
        int Q ;
        scanf ("%d" , &Q) ;
        while (Q--) {
            int k ;
            scanf ("%d" , &k) ;
            int lca = -1 ;
            for (int i = 1 ; i <= k ; i++) {
                int u ; scanf ("%d" , &u) ;
                u++ ;
                if (dist[u] >= inf) {
                    continue ;
                }
                if (lca == -1) lca = u ;
                else lca = LCA(lca,u) ;
            }
            if (lca == -1) {
                printf ("0\n") ;
            }
            else {
                printf ("%d %d\n" , depth[lca] + 1 , subTree[lca]) ;
            }
        }
    }
}
