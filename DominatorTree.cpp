#include <bits/stdc++.h>

#define mp make_pair
#define pb push_back
#define xx first
#define yy second
#define i64 long long int
#define MEM(a,x) memset(a,x,sizeof(x))
#define INF 1000000000
#define maxn 200005


using namespace std ;

namespace DominatorTree{
/*
Dominator Tree for General Graph ,Tr[u] stores all the
immediate children of node u (does not store the parent) in
the dominator tree. at first initialize with number of nodes.
then add edges(directed edges). call buildDominatorTree(r) ,
where r is the root. then just call dominator(u,v) to check
if v is u's dominator it returns false in case either u or v
is not connected to the root
*/
const int N = 202400;
vector <int> G[N] , pred[N] , dom[N] , Tr[N] ;
int old[N] , dfn[N] , up[N] , f[N] , semi[N] , g[N] , idom[N] , cnt ;
int n , m ;
int Time , st[N] , en[N] ;

void init(int _n) {
    for (int i = 0 ; i < N ; i++) G[i].clear() , pred[i].clear() , dom[i].clear() , Tr[i].clear() ;
    memset (old , 0 , sizeof old) ;
    memset (dfn , 0 , sizeof dfn) ;
    memset (f , 0 , sizeof f) ;
    memset (up , 0 , sizeof up) ;
    memset (old , 0 , sizeof old) ;
    memset (g , 0 , sizeof g) ;
    memset (idom , 0 , sizeof idom) ;
    memset (st , -1 , sizeof st) ;
    memset (en , -1 , sizeof en) ;
    n = _n ;
    cnt = 0 ; Time = 0 ;
}

void addEdge(int u , int v){ return G[u].push_back(v) ; }

void dfs(int u){
        old[dfn[u]=++cnt] = u ;
        semi[cnt] = g[cnt] = f[cnt] = cnt;
        for(int v : G[u]){
                if(!dfn[v]){
                        dfs(v);
                        up[dfn[v]] = dfn[u];
                }
                pred[dfn[v]].push_back(dfn[u]);
        }
}

int ff(int x) {
        if(x == f[x]) return x;
        int y = ff(f[x]) ;
        if(semi[g[x]] > semi[g[f[x]]])
                g[x] = g[f[x]];
        return f[x] = y;
}

void dfs1(int u)
{
    Time++ ;
    st[u] = Time ;
    for(int i=0 ; i<Tr[u].size() ; i++)
    {
        dfs1( Tr[u][i] ) ; //par is not stored in Tr[u]
    }
    Time++ ;
    en[u] = Time ;
}

void buildDominatorTree(int r){
        dfs(r);
        for(int y = cnt ; y >= 2 ; y--){
                for(int z : pred[y]) {
                        ff(z);
                        semi[y]=min(semi[y],semi[g[z]]);
                }
                dom[semi[y]].push_back(y);
                int x=f[y]=up[y];
                for(int z:dom[x]){
                        ff(z);
                        idom[z]=semi[g[z]]<x? g[z]:x;
                }
                dom[x].clear();
        }
        for(int y = 2 ; y <= cnt ; ++y){
                if(idom[y]!=semi[y])
                        idom[y]=idom[idom[y]];
                dom[idom[y]].push_back(y);
        }
        idom[r] = 0 ;
        for (int i = 1 ; i <= n ; i++) {
        for (int j = 0 ; j < dom[i].size() ; j++) {
            Tr[old[i]].push_back(old[dom[i][j]]) ;
        }
        }
        dfs1(r) ;
    }
    bool dominator( int u,int v )
    {
        //returns true if v is u's dominator
        if(st[u]==-1 || st[v]==-1) return false ;//if u or v is not connected to the root
        if( st[u] >= st[v] && st[u]<= en[v] ) return true ;
        return false ;
    }
}

vector <int> g[maxn], e[maxn] ;
int dis[maxn] ;
void dijkstra(int n)
{
    int i, j, k, l, m ;
    priority_queue < pair<int,int> > pq ;
    for(i=1 ; i<=n ; i++ ) dis[i] = INF ;
    dis[1] = 0 ;
    pq.push( mp(0,1) ) ;
    while( !pq.empty() )
    {
        pair<int,int> p = pq.top() ;
        pq.pop() ;
        if( dis[p.yy] != -p.xx ) continue ;
        for(i=0 ; i<g[p.yy].size() ; i++)
        {
            int city = g[ p.yy ][i] ;

            if( dis[city] > -p.xx + e[ p.yy][i]  )
            {
                dis[city] = -p.xx + e[ p.yy][i] ;
                pq.push(  mp( -dis[city], city ) ) ;
            }
        }
    }
    return ;
}

struct data
{
    int u, v, w ;
} edge[maxn];

int main()
{
    int i, j, k, l, m, n, t=1, tc ;

    scanf("%d",&tc);

    while(t<=tc)
    {
        scanf("%d %d",&n,&m) ;

        for(i=1 ; i<=n ; i++) g[i].clear(), e[i].clear() ;

        for(i=1 ; i<=m ; i++)
        {
            int u , v , w ;
            scanf("%d %d %d",&u,&v,&w) ;

            edge[i].u = u ; edge[i].v = v ; edge[i].w = w ;
            g[ u ].pb( v  ) ;
            e[ u ].pb( w ) ;
        }

        dijkstra(n) ;

  //      for(i=1 ; i<=n ; i++) printf("dis[%d]: %d\n",i,dis[i]) ;

        DominatorTree::init(n+m) ;
        for(i=1 ; i<=m ; i++)
        {
            int u = edge[i].u , v = edge[i].v , w=edge[i].w ;
            if( dis[u] +  w == dis[ v ] )
            {
                DominatorTree::addEdge(u,n+i) ;
                DominatorTree::addEdge(n+i,v) ;
            }
        }
        DominatorTree::buildDominatorTree(1) ;

   /*     for(i=1; i<=n+m ; i++)
        {
            printf("%d:",i) ;
            for(j=0 ; j<dmt.Tr[i].size() ; j++) printf(" %d",dmt.Tr[i][j]) ;
            printf("\n") ;
        }

        for(i=1 ; i<=n+m ; i++) printf("st[%d]: %d en[%d]: %d\n",i,dmt.st[i],i,dmt.en[i]) ; */

        long long int ans = 0LL ;

        for(i=1 ; i<=m ; i++)
        {
            int u = edge[i].u, v = edge[i].v, w = edge[i].w ;

            long long int a, b ;

            if( dis[u] == dis[v] )
            {
                if(w==0)
                {
                    b = 0 ;

                    if( DominatorTree::dominator(v,n+i) )
                    {
                        a = 0 ;
                    }
                    else a = -1 ;
                }
                else
                {
                    a = -1 ;
                    b = w ;
                }
            }
            else
            {
                if( dis[u] + w == dis[v] )
                {
                    b = 0 ;
                    if( DominatorTree::dominator(v,n+i)  ) a = 0 ;
                    else a = -1 ;
                }
                else
                {
                    a = -1 ;
                    b = dis[u] + w - dis[v] ;
                }
            }

            ans += (i64)i*a + (i64)i*(i64)i*b ;

        //    printf("%d %lld %lld\n",i,a,b) ;
        }
        printf("Case %d: %lld\n",t++,ans) ;
    }

    return 0 ;
}
