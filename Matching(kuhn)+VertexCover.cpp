#include <bits/stdc++.h>
#define pf printf
#define sf scanf
#define INF 1000000000000000001LL
#define PI (acos(-1.0))
#define DBG printf("Hi\n")
#define loop(i,n) for(i =1 ; i<=n; i++)
#define mp make_pair
#define pb push_back
#define mod 1000000007
#define maxn 100005
#define ff first
#define ss second
#define sq(x) ((x)*(x))
#define eps 0.0000000001
#define i64 long long int
#define ui64 unsigned long long int

using namespace std ;

int pairs[2005] ;
bool vis[2005] ;
vector <int> g[2005] , g1[2005] ;

bool dfs1(int u)
{
    if(vis[u]) return false ;
    vis[u] = true ;

    for(int i = 0 ; i<g[u].size() ; i++)
    {
        int v = g[u][i] ;
        if( pairs[v]==-1 || dfs1(pairs[v])  ){
            pairs[v] = u ;
            pairs[u] = v ;
     //       printf("printing from dfs %d %d\n",u,v) ;
            return true ;
        }
    }
    return false ;
}

int kuhn(int r, int c)
{
    memset(pairs,-1,sizeof(pairs)) ;

    int ret = 0 ;

    for(int i=1 ; i<=r ; i++)
    {
        memset( vis , 0 , sizeof(vis) ) ;
        if(dfs1(i)) ret++ ;
    }
    return ret ;
}

void dfs2(int u)
{
    if(vis[u]) return ;
    vis[u] = 1 ;
    for(int i=0 ; i<g1[u].size() ; i++) dfs2(g1[u][i]) ;
    return ;
}


int main()
{
    int i , j , k , l , m , n , r , c , u , v , ans ;

    while( sf("%d %d %d",&r,&c,&n)  )
    {
        if(r==0 &&c==0 && n==0) break ;

        for(i=1 ; i<=n ; i++)
        {
            sf("%d %d",&u,&v) ;
            g[u].pb(v+r) ;
            g[v+r].pb(u) ;
        }

        ans = kuhn(r,c) ;

    //    for(i=1 ; i<=r ; i++) pf("%d %d\n",i,pairs[i]-r) ;
     //   for(i=r+1 ; i<=r+c ; i++) pf("%d %d\n",i-r,pairs[i]) ;


        for(i=1 ; i<=r ; i++)
        {
            for(j=0 ; j<g[i].size() ; j++  )
            {
                if( pairs[i] == g[i][j] ) g1[ g[i][j] ].pb(i) ;
                else g1[i].pb( g[i][j] ) ;
            }
        }
        memset(vis,0,sizeof(vis)) ;

        for( i=1 ; i<=r ; i++ )
        {
            if( pairs[i]==-1 ) dfs2(i) ;
        }

        pf("%d",ans) ;

        for(i=1 ; i<=r+c ; i++)
        {
            if( pairs[i]!=-1 )
            {
                if( i<=r && !vis[i] ) pf(" r%d",i) ;
                else if( i>r && vis[i] ) pf(" c%d",i-r) ;
            }
        }
        pf("\n") ;
        for(i=1 ; i<=r+c ; i++){
            g[i].clear() ;
            g1[i].clear() ;
        }
    }

    return 0 ;
}
