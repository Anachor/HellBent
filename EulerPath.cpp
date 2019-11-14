#include <bits/stdc++.h>

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define IN freopen("testing.txt","r",stdin)
#define OUT freopen("output.txt","w",stdout)
#define FOR(i,a,b) for(i=a ; i<=b ; i++)
#define DBG pf("Hi\n")
#define INF 1000000000
#define i64 long long int
#define eps (1e-8)
#define xx first
#define yy second
#define ln 17
#define off 2

//using namespace __gnu_pbds;
using namespace std ;

typedef pair<int, int> pi ;
//typedef tree< pi, null_type, less<pi>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const i64 mod = 1000000007LL ;

#define maxn 500005

/*
     *os.find_by_order(k) -> returns the k'th smallest element (indexing starts from 0)
      os.order_of_key(v)  -> returns how many elements are strictly smaller than v
*/

int c[maxn] , d[maxn] ;

map< int , multiset<int> > g ;
map <int,int> vis ;


void dfs1(int u)
{
    vis[u] = 1 ;
    for( auto v : g[u] ) if( vis.find(v) == vis.end() ) dfs1(v) ;
}

///--------Euler path printing-----------///
//just call dfs2 with the node you want to start your path
//at first you need to make sure, the graph is connected and euler path exist
vector <int> ans ;
void dfs2(int u)
{
    while( (int)g[u].size() !=0 )
    {
        int v = *g[u].begin() ;
        g[u].erase( g[u].find(v) ) ;
        g[v].erase( g[v].find(u) ) ;
        dfs2(v) ;
    }
    ans.pb(u) ;
}
///--------Euler path printing-----------///


int main()
{
    int n  ;

    scanf("%d",&n) ;

    for(int i=1 ; i<n ; i++) scanf("%d",&c[i]) ;
    for(int i=1 ; i<n ; i++) scanf("%d",&d[i]) ;

    for(int i=1 ; i<n ; i++)
    {
        if( c[i] > d[i] )
        {
            printf("-1\n") ;
            return 0 ;
        }
        g[ c[i] ].insert( d[i] ) ;
        g[ d[i] ].insert( c[i] ) ;
    }

    int src = c[1] , cnt = 0 ;

    for( auto it : g )
    {
        if( (int)it.second.size() & 1 )
        {
            cnt++ ;
            src = it.first ;
        }
    }

    dfs1( src ) ;

    if( vis.size() != g.size() || ( cnt!=0 && cnt!=2 ) )
    {
        printf("-1\n") ;
        return 0 ;
    }

    //call for printing euler path
    dfs2(src) ;

    for(int i=0 ; i<ans.size() ; i++)
    {
        printf("%d",ans[i]) ;
        if( i == (int)ans.size() - 1 ) printf("\n") ;
        else printf(" ") ;
    }

    return 0 ;
}
