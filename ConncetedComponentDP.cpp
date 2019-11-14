#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define PI ( acos(-1.0) )
#define mod 1000000007LL
#define IN freopen("strings.in","r",stdin)
#define OUT freopen("strings.out","w",stdout)
#define FOR(i,a,b) for(i=a ; i<=b ; i++)
#define DBG pf("Hi\n")
#define INF 1000000000
#define i64 long long int
#define eps (1e-8)
#define xx first
#define yy second
#define ln 17
#define off 2

using namespace __gnu_pbds;
using namespace std ;

typedef pair<int, int> pi ;
typedef tree< pi, null_type, less<pi>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

i64 dp[102][32][12][12][2][2] , M ;
int a[102] ;

i64 f( int n ,int r , int k , int c , int st , int en )
{
    if( n==0 || c < 0 || st < 0 || en < 0 ) return 0 ;
    r = ( r + a[n]*( 2*c + st + en ) )%M ;
 //   printf("%d %d %d %d %d %d\n",n,r,k,c,st,en) ;
    if( dp[n][r][k][c][st][en] != -1 ) return dp[n][r][k][c][st][en] ;

//    int rem = r ;

    i64 ans = f(n-1,r,k,c,st,en) ; /* it is not used */

    if( k==1 )
    {
        if( c==0 && (st||en) && r==0 ) ans++ ; /* if this is the last element to take
        then is should either connect st and en , or be the first element or last */
    }
    else{

        if(st==0) ans += ( f( n-1, r , k-1 , c , 1 , en ) + f( n-1 , r , k-1 , c-1 , 1 , en )*c ) ; // this is starting element
        if(en==0) ans += ( f(n-1,r,k-1,c,st,1) + f( n-1,r,k-1,c-1,st,1)*c ) ; // this is ending element

        ans += f( n-1 , r , k-1 , c+1 , st , en ) ; // created & independent
        ans += f( n-1 , r , k-1, c , st , en)*2*c + f(n-1,r,k-1,c,st,en)*(st+en) ; /* created and connected with some other component
        possibly start or end component */
        ans += (f( n-1 , r , k-1 , c-1 , st , en)*c*(c-1) + f( n-1 , r , k-1, c-1 , st, en )*c*(st+en) ) ;/* created
        and connected between two component */

    }

    return dp[n][r][k][c][st][en] = ans%mod ;
}

int main()
{
    int n , k ;

    scanf("%d %d %d",&n,&M,&k) ;

    for(int i=1 ; i<n ; i++) scanf("%d",&a[i]) ;

    a[n] = 0 ;

    memset(dp,-1,sizeof(dp)) ;

    i64 ans =  f( n , 0 , k , 0 , 0 , 0 ) ;

    ans = (ans%mod + mod)%mod ;

    printf("%lld\n",ans) ;

    return 0 ;
}
