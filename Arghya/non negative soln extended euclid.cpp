#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>/
// #include <ext/pb_ds/tree_policy.hpp>

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
#define ln 17
#define off 2
#define SZ(z) ((int)z.size())

// using namespace __gnu_pbds;
using namespace std ;

// typedef tree< i64, null_type, less<i64>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define maxn 50005

typedef pair<i64, i64> pii;

// f(a,b,c) returns how many non_negative (x,y) are there such that a*x+b*y = c
//tested for (a,b,c) > 0
// for negative (a,b) equation changes

pii extendedEuclid(i64 a, i64 b) { // returns x, y | ax + by = gcd(a,b)

    if(b == 0) return pii( a >= 0 ? 1 : -1 , 0LL);
    else {
        pii d = extendedEuclid(b, a % b);
        return pii(d.yy, d.xx - d.yy * (a / b));
    }

}
i64 gcd(i64 a, i64 b)
{
    if(b==0) return a ;
    return gcd(b,a%b) ;
}
i64 Floor(i64 a, i64 b)
{
    if(b<0) b *= (-1) , a *= (-1) ;
    i64 c = a/b ;
    if( a<0 && b*c!=a ) c-- ;
    return c ;
}
i64 Ceil(i64 a, i64 b)
{
    if(b<0) b *= (-1) , a *= (-1) ;
    i64 c = a/b ;
    if( a>0 && b*c!=a ) c++ ;
    return c ;
}
i64 f( i64 a, i64 b,i64 c )
{
    if( a==0 && b==0 ) return (c==0) ;
    if(a==0) return (c%b == 0) ;
    if(b==0) return (c%a == 0) ;

    i64 g = gcd(a,b) ;
    if(c%g!=0) return 0 ;

    c /= g ;
    a /= g ; b/= g ;

    pii soln = extendedEuclid(a,b) ;

    soln.xx*= c ; soln.yy *= c ;

    i64 lo = Ceil(-soln.xx,b) , hi = Floor(soln.yy,a) ;

    return max( 0LL , hi-lo+1 ) ;
}

int main()
{
    i64 i , j , k , l , m , n ;

    i64 t =1 , tc ;

    i64 a , b , c , p ;

    scanf("%lld",&tc) ;

    while(t<=tc)
    {
        scanf("%lld %lld %lld %lld",&a,&b,&c,&p) ;

        printf("Case %lld: ",t++) ;

        i64 g = gcd( a , gcd(b,c) ) ;

        if(p%g!=0)
        {
            printf("0\n") ;
            continue ;
        }

        a /= g ; b /= g ; c/=g ; p/=g ;

        i64 ans = 0LL ;

        while( p>=0 )
        {
            ans += f(a,b,p) ;
            p -= c ;
        }

        printf("%lld\n",ans) ;
    }

    return 0 ;
}
