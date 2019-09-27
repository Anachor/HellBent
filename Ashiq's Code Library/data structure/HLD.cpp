/// HLD from ARGHYA, yet to get used to

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define IN freopen("transposition-115.txt","r",stdin)
#define OUT freopen("dichromatic.out","w",stdout)
#define FOR(i,a,b) for(i=a ; i<=b ; i++)
#define DBG pf("Hi\n")
#define INF 2000000000
#define i64 long long int
#define eps (1e-8)
#define xx first
#define yy second
#define sq(x)  ((x)*(x))

using namespace __gnu_pbds;
using namespace std ;

#define maxn (1<<18)+5
#define mod 1000000007LL

typedef pair<i64,i64> pii ;
typedef  long long int T ;

struct edge{
    int u , v , c , id ;
    bool operator<(const edge other)const{ return c < other.c ; }
};

namespace MST{
    int par[maxn] ;
    int findPar(int u)
    {
        if( par[u] != u ) return par[u] = findPar( par[u] ) ;
        return u ;
    }

    void findMST( int n , vector < edge > &e )
    {
        //after this function , e[0] to e[n-2] will contain the treeEdges
        //and other would be non-tree Edges

        sort( e.begin() , e.end() ) ;
        for(int i=1 ; i<=n ; i++) par[i] = i ;

        vector <edge> treeEdge , otherEdge ;

        for(int i=0 ; i< e.size() ; i++ )
        {
            int u = e[i].u , v = e[i].v ;
            int pu = findPar(u) , pv = findPar(v) ;
            if( pu==pv ) otherEdge.pb(e[i]) ;
            else{
                par[pu] = pv ;
                treeEdge.pb(e[i]) ;
            }
        }
        e.clear() ;
        for(int i=0 ; i<treeEdge.size() ; i++) e.pb( treeEdge[i] ) ;
        for(int i=0 ; i<otherEdge.size() ; i++) e.pb( otherEdge[i] ) ;
    }
}

int tr[2*maxn] , lazy[2*maxn] , ara[maxn] ;

void relax(int cn, int b, int e)
{
    tr[cn] = min( tr[cn] , lazy[cn] ) ;
    if( b!=e )
    {
        int lc = cn<<1 , rc = lc+1 , m = (b+e)>>1 ;
        lazy[lc] = min( lazy[cn] , lazy[lc] ) ;
        lazy[rc] = min( lazy[cn] , lazy[rc] ) ;
    }
    lazy[cn] = INF ;
}

void update(int cn, int b , int e, int l, int r,int val)
{
    if( lazy[cn] != INF ) relax(cn,b,e) ;
    if( e < l || b > r ) return ;
    if( l<=b && e<=r )
    {
        lazy[cn] = val ;
        relax(cn,b,e) ;
        return ;
    }
    int lc = cn<<1 , rc = lc+1 , m = (b+e)>>1 ;
    update(lc,b,m,l,r,val) ; update(rc,m+1,e,l,r,val) ;
    tr[cn] = max(tr[lc],tr[rc]) ;
}

int query(int cn, int b, int e, int l, int r)
{
    if(lazy[cn]!= INF ) relax(cn,b,e) ;
    if( e < l || b > r ) return -INF;
    if( l<=b && e<=r ) return tr[cn] ;
    int lc = cn<<1 , rc = lc+1 , m = (b+e)>>1 ;
    return max( query(lc,b,m,l,r) , query(rc,m+1,e,l,r) ) ;
}

void build(int cn, int b, int e)
{
    lazy[cn] = INF ;
    if( b==e )
    {
        tr[cn] = ara[b] ;
        return ;
    }
    int lc = cn<<1 , rc = lc+1 , m = (b+e)>>1 ;
    build(lc,b,m) ; build(rc,m+1,e) ;
    tr[cn] = max(tr[lc],tr[rc]) ;
}

namespace hld{
    int in[maxn] , out[maxn] , sub[maxn] , t = 1 , nxt[maxn] , depth[maxn], par[maxn] , n ;
    vector <int> g[maxn] ;
    void init(int _n)
    {
        n = _n ;
        for(int i=0 ; i<=n ; i++) g[i].clear() ;
    }

    void addEdge(int u, int v)
    {
        g[u].pb(v) ;
        g[v].pb(u) ;
    }

    void dfsSZ(int u)
    {
        sub[u] = 1 ;

        for(int i=0 ; i<g[u].size() ; i++)
        {
            int v = g[u][i] ;
            for(int j=0 ; j<g[v].size() ; j++)
            {
                if( g[v][j] == u )
                {
                    g[v].erase( g[v].begin() + j ) ;
                    break ;
                }
            }
            dfsSZ(v) ;
            sub[u] += sub[v] ;
            if( sub[v] > sub[ g[u][0] ] ) swap( g[u][0] , g[u][i] ) ;
        }
    }

    void dfsHLD(int u)
    {
        in[u] = ++t ;
        for(int i=0 ; i<g[u].size() ; i++)
        {
            int v = g[u][i] ;
            par[v] = u ;
            depth[v] = depth[u] + 1 ;
            if( i==0 ) nxt[v] = nxt[u] ;
            else nxt[v] = v ;

            dfsHLD(v) ;
        }
        out[u] = t ;
    }

    void preprocess(int root)
    {
        dfsSZ(root) ;
        t = 0 ; nxt[root] = root ;
        depth[root] = 1 ;
        dfsHLD(root) ;
    }

    int hldQuery( int u , int v )
    {
        int ans = -INF ;
        while( nxt[u] != nxt[v] )
        {
            if( depth[ nxt[u] ] < depth[ nxt[v] ] )
            {
                ans = max( ans , query(1,1,n, in[ nxt[v] ] , in[v] ) ) ;
                // do you thing here ( from in[v] to in[ nxt[v] ] )
                v = par[ nxt[v] ] ;
            }
            else{
                ans = max( ans , query(1,1,n, in[ nxt[u] ] , in[u] ) ) ;
                // do your thing here ( from in[u] to in[ nxt[u] ] )
                u = par[ nxt[u] ] ;
            }
        }
        int lc ;
        if( depth[u] > depth[v] ) swap(u,v) ;
        lc = u ;

        //here lc is the lca
        //if you are working on node , not on edge, then update/query upto u also
        //otherwise update/query from in[u]+1 to in[v]

        ans = max( ans , query(1,1,n,in[u]+1,in[v]) ) ;

        return ans ;
    }

    void hldUpdate( int u , int v , int val )
    {
        while( nxt[u] != nxt[v] )
        {
            if( depth[ nxt[u] ] < depth[ nxt[v] ] )
            {
                update(1,1,n,in[ nxt[v] ] , in[v] , val ) ;
                // do you thing here ( from in[v] to in[ nxt[v] ] )
                v = par[ nxt[v] ] ;
            }
            else{
                update(1,1,n,in[ nxt[u] ] , in[u] , val ) ;
                // do your thing here ( from in[u] to in[ nxt[u] ] )
                u = par[ nxt[u] ] ;
            }
        }
        int lc ;
        if( depth[u] > depth[v] ) swap(u,v) ;
        lc = u ;

        //here lc is the lca
        //if you are working on node , not on edge, then update/query upto u also
        //otherwise update/query from in[u]+1 to in[v]

        update(1,1,n,in[u]+1,in[v],val) ;

        return ;
    }

}

int ans[maxn] ;

int main()
{
    int n , m ;

    vector < edge > e ;

    scanf("%d %d",&n,&m) ;

    for( int i=1 ; i<=m ; i++ )
    {
        int u ,v , c ;
        scanf("%d %d %d",&u,&v,&c) ;
        e.pb( {u,v,c,i} ) ;
    }

    MST::findMST( n , e ) ;

    hld::init(n) ;

    for(int i=0 ; i<n-1 ; i++)
    {
        hld::addEdge( e[i].u , e[i].v ) ;
    }

    hld::preprocess(1) ;

    for(int i=0 ; i<n-1 ; i++)
    {
        int u = e[i].u , v =  e[i].v , c= e[i].c ;

        if( hld::depth[u] > hld::depth[v] ) swap(u,v) ;

        ara[ hld::in[v] ] = e[i].c ;
    }

    ara[ hld::in[1] ] = INF ;
    build(1,1,n) ;

    for(int i=n-1 ; i<m ; i++)
    {
        int u = e[i].u , v =  e[i].v , c= e[i].c ;

        ans[ e[i].id ] = hld::hldQuery(u,v) - 1 ;
    }

    for(int i=1 ; i<=n ; i++) ara[i] = INF ;
    build(1,1,n) ;

    for(int i=n-1 ; i<m ; i++)
    {
        int u = e[i].u , v =  e[i].v , c= e[i].c ;
        hld::hldUpdate(u,v,c) ;
    }

    for(int i=0 ; i<n-1 ; i++)
    {
        int u = e[i].u , v =  e[i].v , c= e[i].c ;
        int res = hld::hldQuery(u,v) ;
        if(res==INF) ans[ e[i].id ] = -1 ;
        else ans[ e[i].id ] = res-1 ;
    }

    for(int i=1 ; i<=m ; i++) printf("%d ",ans[i]) ;
    printf("\n") ;

    return 0 ;
}
