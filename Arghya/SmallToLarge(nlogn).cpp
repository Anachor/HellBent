#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>/
// #include <ext/pb_ds/tree_policy.hpp>

#define pb push_back
#define mp make_pair

#define mod 998244353LL
#define IN freopen("input.txt","r",stdin)
#define OUT freopen("output.txt","w",stdout)
#define FOR(i,a,b) for(i=a ; i<=b ; i++)
#define DBG printf("Hi\n")
#define INF 1000000000
#define i64 long long int
#define eps (1e-8)
#define xx first
#define yy second
#define ln 17
#define off 2
#define SZ(z) ((int)z.size())
#define sq(x) ((x)*(x))

#define FastIO ios_base::sync_with_stdio(false); cin.tie(NULL)

#define EPS 1e-7

// using namespace __gnu_pbds;
using namespace std ;

// typedef tree< i64, null_type, less<i64>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

typedef pair<i64, i64> pii;

#define maxn 500005
#define alpha 22

int ans[maxn] ;
int lenOff[maxn] , mask[maxn]  ;
int len[(1<<alpha)+2] ;
int sub[maxn] ;
vector <int> g[maxn] , e[maxn] ;

void Add(int u , int root , int curMask, int l)
{
    len[ (curMask^mask[root]) ] = max( len[ (curMask^mask[root]) ] , l-lenOff[root] ) ;

    for(int i=0 ; i<g[u].size() ; i++)
    {
        int v = g[u][i] ;
        Add( v , root , (curMask^(1<<e[u][i])) , l+1 ) ;
    }
}

void Remove(int u , int root , int curMask, int l)
{
    len[ (curMask^mask[root]) ] = -INF ;

    for(int i=0 ; i<g[u].size() ; i++)
    {
        int v = g[u][i] ;
        Remove( v , root , (curMask^(1<<e[u][i])) , l+1 ) ;
    }
}

void addAnswer(int u , int root , int curMask, int l)
{
    ans[root] = max( ans[root] , len[ (curMask^mask[root]) ] + lenOff[root] + l ) ;

    for(int i=0 ; i<alpha ; i++)
    {
        int m = (curMask^(1<<i)) ;
        ans[root] = max( ans[root] , len[ m^mask[root] ] + lenOff[root] + l ) ;
    }

    for(int i=0 ; i<g[u].size() ; i++)
    {
        int v = g[u][i] ;
        addAnswer( v , root , (curMask^(1<<e[u][i])) , l+1 ) ;
    }
}

void dfs(int u, bool keep)
{
    bool hasChild = ( (int)g[u].size() > 0 ) ;

    for(int i=1 ; i<g[u].size() ; i++)
    {
        dfs(g[u][i],0) ;
    }
    if( hasChild )
    {
        int bigChild = g[u][0] ;
        dfs( bigChild , 1) ;
        mask[u] = (mask[bigChild]^( 1<<e[u][0] )) ;
        lenOff[u] = lenOff[ bigChild ] + 1 ;
    }

    len[ mask[u] ] = max( len[ mask[u] ] , -lenOff[u] ) ;

    for(int i=1 ; i<g[u].size() ; i++)
    {
        addAnswer( g[u][i] , u , (1<<e[u][i]) , 1 ) ;
        Add( g[u][i] , u , (1<<e[u][i]) , 1 ) ;
    }

    ans[u] = max( ans[u] , 0 ) ;

    ans[u] = max( ans[u] , len[ mask[u] ] + lenOff[u] ) ;

    for(int i=0 ; i<alpha ; i++)
    {
        ans[u] = max( ans[u] , len[ (mask[u]^(1<<i)) ] + lenOff[u] ) ;
    }

    for(auto v:g[u]) ans[u] = max( ans[u] , ans[v] ) ;

    if( keep == 0 ) Remove(u,u,0,0) ;
}

void dfsSize(int u )
{
    sub[u] = 1 ;
    for( int i=0 ; i<g[u].size() ; i++ )
    {
        int v = g[u][i] ;
        dfsSize(v) ;
        sub[u] += sub[v] ;
        if( sub[v] > sub[ g[u][0] ] )
        {
            swap( g[u][0] , g[u][i] ) ;
            swap( e[u][0] , e[u][i] ) ;
        }
    }
}

int main()
{
    int n ;
    scanf("%d",&n) ;

    for(int i=2 ; i<=n ; i++)
    {
        int p ;
        char s[4] ;
        scanf("%d %s",&p,s) ;
        g[p].pb(i) ; e[p].pb( s[0]-'a' ) ;
    }

    for(int i=0 ; i<(1<<alpha) ; i++) len[i] = -INF ;

    dfsSize(1) ;
    dfs(1,1) ;

    for(int i=1 ; i<=n ; i++)
    {
        printf("%d ",ans[i]) ;
    }
    printf("\n") ;

    return 0 ;
}
