//LOJ-1308 Ant Network

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define PI ( acos(-1.0) )
#define mod 1000000007LL
#define IN freopen("testing.txt","r",stdin)
#define OUT freopen("output.txt","w",stdout)
#define FOR(i,a,b) for(i=a ; i<=b ; i++)
#define DBG pf("Hi\n")
#define INF 1000000000000000000LL
#define i64 long long int
#define eps (1e-8)
#define xx first
#define yy second
#define ln 17
#define off 2

using namespace __gnu_pbds;
using namespace std ;

typedef pair<pair<i64, i64>,int> pi ;
typedef tree< pi, null_type, less<pi>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define maxn 100005

namespace BCT
{
    const int mx = 100005 ; // max( number of edge , number of node )
    bool isCutPoint[mx] ;
    int low[mx] , pre[mx] , cnt2vcc , used[mx] , Timer = 0 ;
    vector <int> biComp[mx] ;
    int n , m ;
    struct Edge{
        int v , id ;
    };
    vector <Edge> g[mx] ;
    vector <int> bridges ; //for bridge
    stack  <int> stk ;

    void init(int _n, int _m)
    {
        n = _n ; m = _m ;
        for(int i=1 ; i<=max(n,m) ; i++) g[i].clear() , biComp[i].clear() ;
        bridges.clear() ; // for bridge
    }

    void addEdge( int u, int v, int id )
    {
        g[u].pb( {v,id} ) ; g[v].pb({u,id}) ;
    }

    void dfs(int u , int par )
    {
    //    printf("node-> %d par: %d edgeId: %d\n",u,par,edgeId) ;
        pre[u] = ++Timer ; low[u] = pre[u] ;

        int chCnt = 0 ;

        for(int i=0 ; i<g[u].size() ; i++)
        {
            int edgeId = g[u][i].id ;

            if( used[ edgeId ] ) continue ;

            used[ edgeId ] = true ;
            stk.push( edgeId ) ;

            int v = g[u][i].v ;

            if( pre[v]==-1 )
            {
                dfs( v , u ) ;

                low[u] = min( low[u] , low[v] ) ;
                if( low[ v ] == pre[ v ]  ) bridges.pb(edgeId) ;
                if( low[v] >= pre[u] )
                {
                    cnt2vcc++ ;
                    while( stk.size() > 0 )  //making component
                    {
                        biComp[cnt2vcc].pb( stk .top() ) ;
                        stk.pop() ;
                        if( biComp[cnt2vcc].back()==edgeId ) break ;
                    }

                    if(par!=0) isCutPoint[u] = true ; //checking if non-root
                }
                chCnt++ ;
            }
            else low[u] = min( low[u] , pre[v] ) ;
        }

        if(chCnt > 1 && par==0) isCutPoint[u] = true ; //checking for root

        return ;
    }

    int find2VCC()
    {
        int i , j ;
        Timer = 0 ;
        for(i=1 ; i<=m ; i++) used[i] = false ;
        for(i=1 ; i<=n ; i++)
        {
            isCutPoint[i] = false ;
            pre[i] = -1 ;
        }
        cnt2vcc = 0 ;
        for(i=1; i<=n ; i++)
        {
            if( pre[i]==-1 ) dfs(i,0) ;
        }
    }
}

struct Edge{
    int u , v , id ;
}edge[maxn];

int main()
{
    int i , j , k , l , m , n , t=1 , tc ;

    scanf("%d",&tc) ;

    while( t<=tc )
    {
        scanf("%d %d",&n,&m) ;

        BCT::init(n,m) ;

        for(i=1; i<=m ; i++)
        {
            int u , v ;
            scanf("%d %d",&u,&v) ;
            u++ ; v++ ;
            edge[i] = {u,v,i} ;
            BCT::addEdge(u,v,i) ;
        }

        BCT::find2VCC() ;

        int cntVcc = BCT::cnt2vcc ;

        int ans1 ;
        unsigned long long int ans2 ;

        if( cntVcc==1 )
        {
            ans1 = 2 ; ans2 = (n*(n-1))/2LL ;
        }
        else{
            ans1 = 0 , ans2=1LL ;
            for(i=1; i<=cntVcc ; i++)
            {
                set <int> nodes ;
                for(j=0 ; j<BCT::biComp[i].size() ; j++)
                {
                    int id= BCT::biComp[i][j] ;
                    nodes.insert( edge[id].u ) ; nodes.insert( edge[id].v ) ;
                }
                set<int> :: iterator it = nodes.begin() ;
                int artCnt = 0 ;
                while( it!=nodes.end() )
                {
                    if( BCT::isCutPoint[*it] ) artCnt++ ;
                    it++ ;
                }
                if( artCnt==1 )
                {
                    ans1++ ;
                    ans2 *= (1LL*( (int)nodes.size() - artCnt )) ;
                }
            }

        }

        printf("Case %d: %d %llu\n",t++,ans1,ans2) ;

  /*      for(i=1 ; i<=n ; i++)
        {
            printf("%d-->%d\n",i,BCT::isCutPoint[i]) ;
        }
        for(i=1 ; i<=cntVcc ; i++)
        {
            for(j=0 ; j<BCT::biComp[i].size() ; j++ ) printf("%d ",BCT::biComp[i][j]) ;
            printf("\n") ;
        }
*/
    }

    return 0 ;
}
/*
14 17
1 2
1 3
2 3
3 4
4 6
5 6
3 5
6 7
6 8
7 8

9 10
9 11
9 12
11 12
10 13
13 14
10 14
*/
