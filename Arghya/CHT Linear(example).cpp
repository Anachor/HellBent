#include <bits/stdc++.h>

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define IN freopen("input.txt","r",stdin)
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

#define maxn 200005

/*
     *os.find_by_order(k) -> returns the k'th smallest element (indexing starts from 0)
      os.order_of_key(v)  -> returns how many elements are strictly smaller than v
*/

struct Line{
    i64 m , c , id ;
    i64 f(i64 x){ return x*m + c ; }
    i64 iSect( Line other ) {
         // floored division
         i64 a = c - other.c , b = other.m - m ;
		return a / b - ((a ^ b) < 0 && a % b);
    }
    bool operator<(const Line& o)const{
        return mp(c,id) < mp(o.c,o.id) ;
    }
};

//for minimization
// slope increasing , query point increasing

struct chtLinear{

    deque <Line> dq ;

    void addLine( i64 m  , i64 c , i64 id )
    {
        if( !dq.empty() && m==dq.front().m ) dq[0] = min( dq[0] , {m,c,id} ) ;
        else dq.push_front( {m,c,id} ) ;
        Line l = dq[0] ; dq.pop_front() ;
        while( (int)dq.size() >= 2 && l.iSect(dq[0]) > dq[0].iSect(dq[1]) ) dq.pop_front() ;
        dq.push_front(l) ;
     }
    pair<i64,i64> f(i64 x)
    {
        while( (int)dq.size() > 1 && dq[0].f(x) >= dq[1].f(x) ) dq.pop_front() ;
        return mp( dq[0].id , dq[0].f(x) ) ;
    }
}ch;

int main()
{
/*
    cout<<dq[0]<<"  "<<dq[1]<<endl ;

    ch.addLine( 1 , -1 , 1 ) ;
    ch.addLine( -1, 1 , 2 ) ;

    pair<ll,ll> p1 = ch.query(0) , p2 = ch.query(1) , p3 = ch.query(2) ;

    cout<<p1.xx<<" "<<p2.xx<<" "<<p3.xx<<endl ;
    cout<<p1.yy<<" "<<p2.yy<<" "<<p3.yy<<endl ;

*/
    i64 n , m ;
    scanf("%lld %lld",&n,&m) ;

    ch.addLine(0,0,1) ;

    i64 S = 0 , B = 0, Sum = n ;

    for(int i=1 ; i<=m  ; i++)
    {
        int q ;

        scanf("%d",&q) ;

        if(q==1)
        {
            S = 0 , B = 0 ;
            ch.dq.clear() ;
            ch.addLine(0,0,1) ;
            i64 a ;
            scanf("%lld",&a) ;
            Sum += a ;
        }
        if(q==2)
        {
            i64 a ;
            scanf("%lld",&a) ;
            ch.addLine( (Sum) , ( - B - Sum*S) , Sum+1 ) ;
            Sum += a ;
        }
        if(q==3)
        {
            i64 b, s;
            scanf("%lld %lld",&b,&s) ;
            B += b ;
            S += s ;
        }
        pair<i64,i64> p = ch.f(S) ;
        printf("%lld %lld\n",p.xx, p.yy + B) ;
    }

    return 0 ;
}
/*
5 100
3 4 5
2 1
*/
