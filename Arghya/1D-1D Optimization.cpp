//http://www.codah.club/tasks.php?show_task=5000000624
//Batch Scheduling
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define PI ( acos(-1.0) )
#define mod 1000000007
#define IN freopen("nocross.in","r",stdin)
#define OUT freopen("nocross.out","w",stdout)
#define FOR(i,a,b) for(i=a ; i<=b ; i++)
#define DBG pf("Hi\n")
#define INF 2000000000
#define i64 long long int
#define eps (1e-8)
#define xx first
#define yy second
#define LOG 19
#define off 2

using namespace __gnu_pbds;
using namespace std ;

typedef tree< pair<int,int>, null_type, less< pair<int,int> >, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define maxn 1000005

int dp[maxn] ;
int t[maxn] , f[maxn] ;
int n , s ;

int w( int i, int x )
{
    return ( t[x]-t[i]+s )*( f[n]-f[i] ) ;
}

int main()
{
    scanf("%d %d",&n,&s) ;

    for(int i=1 ; i<=n ; i++)
    {
        scanf("%d %d",&t[i],&f[i]) ;
        t[i] += t[i-1] ;
        f[i] += f[i-1] ;
    }

    vector < pair<int,int> > vp ; // pos , best-k

    vp.pb( mp( 0 , 0 ) ) ;

    for(int x=1 ; x<=n ; x++)
    {
        int idx = upper_bound( vp.begin() , vp.end() , mp( x , n+1 ) ) - vp.begin() ;
        idx-- ;

        dp[x] = dp[ vp[idx].yy ] + w( vp[idx].yy , x ) ;

        while( (int)vp.size() > 0 )
        {
            if( vp.back().xx > x && dp[x] + w( x , vp.back().xx ) <= dp[ vp.back().yy ] + w( vp.back().yy , vp.back().xx ) ) vp.pop_back();
            else break ;
        }

        if( vp.size() == 0 ) vp.push_back( mp( 0 , x ) ) ;
        else{

            int lo = max(vp.back().xx,x+1) , hi = n ;

            if( lo > hi || dp[ vp.back().yy ] + w( vp.back().yy  , hi ) <= dp[x] + w( x , hi ) ) continue ;

            while( lo < hi )
            {
                int mid = (lo+hi)/2 ;

                if( dp[ vp.back().yy ] + w( vp.back().yy , mid ) <= dp[x] + w( x , mid ) ) lo = mid + 1 ;
                else hi = mid ;
            }

            vp.pb( mp( lo , x ) ) ;
        }
    }

    printf("%d\n",dp[n]) ;

    return 0 ;
}
