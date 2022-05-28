
/*
Add a point , and add a rectangle .
After each addition answer how many (rectangle,point) pair exists such that point is in rectangle.
*/

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define PI ( acos(-1.0) )
#define mod 1000000007LL
#define IN freopen("C.in","r",stdin)
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

using namespace __gnu_pbds;
using namespace std ;

typedef pair<int, int> pii ;
typedef tree< pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define maxn 300005

/*
     *os.find_by_order(k) -> returns the k'th smallest element (indexing starts from 0)
      os.order_of_key(v)  -> returns how many elements are strictly smaller than v
*/
ordered_set os[maxn] ;
struct DataStructure
{
public:
    ordered_set os[maxn] ;
    int mxX , cur = 0 ;
    void init( int _mxX )
    {
        mxX = _mxX ;
        for(int i=1 ; i<=mxX ; i++) os[i].clear() ;
        cur = 0 ;
    }
    void add(int x ,int y)
    {
        cur++ ;
        pii element = mp( y, cur ) ;
        while( x<= mxX  )
        {
            os[x].insert( element ) ;
            x += (x&(-x)) ;
        }
    }
    int query( int x ,int y )
    {
        int sum = 0 ;
        pii element = mp( y, cur+1 ) ;
        while( x>0 )
        {
            sum += os[x].order_of_key(element) ;
            x -= (x&(-x));
        }
        return sum ;
    }
};

struct Rectangle{
    int x1 , y1  , x2, y2 ;
}rect[maxn];
struct Point
{
    int x, y ;
}point[maxn];
set<int> xSet , ySet ;
map<int,int> xMap, yMap ;
int qType[maxn] ;

int main()
{
    int i , j , k , l , m , n , t ;

    scanf("%d",&n) ;

    int cntPoint = 0 , cntRect = 0 ;

    for(i=1 ; i<=n ; i++)
    {
        scanf("%d",&t) ;
        qType[i] = t ;
        if(t==1)
        {
            cntPoint++ ;
            scanf("%d %d",&point[cntPoint].x,&point[cntPoint].y) ;
            xSet.insert( point[cntPoint].x ) ;
            ySet.insert( point[cntPoint].y ) ;
        }
        else{
            cntRect++ ;
            scanf("%d %d %d %d",&rect[cntRect].x1, &rect[cntRect].y1, &rect[cntRect].x2, &rect[cntRect].y2) ;
            xSet.insert(rect[cntRect].x1 ) ; xSet.insert(rect[cntRect].x2 ) ;
            ySet.insert(rect[cntRect].y1 ) ; ySet.insert(rect[cntRect].y2 ) ;
        }
    }

    set<int> :: iterator it ;
    it = xSet.begin();
    int mxX = 0 ;
    while( it!=xSet.end() )
    {
        xMap[*it] = ++mxX ;
        it++ ;
    }
    it = ySet.begin();
    int mxY = 0 ;
    while( it!=ySet.end() )
    {
        yMap[*it] = ++mxY ;
        it++ ;
    }

    for(i=1 ; i<=cntPoint ; i++)
    {
        point[i].x = xMap[point[i].x] ; point[i].y = yMap[point[i].y] ;
    }
    for(i=1 ; i<=cntRect ; i++)
    {
        rect[i].x1 = xMap[rect[i].x1] ; rect[i].x2 = xMap[rect[i].x2] ;
        rect[i].y1 = yMap[rect[i].y1] ; rect[i].y2 = yMap[rect[i].y2] ;
    }

    DataStructure pt , r1, r2 ;

    pt.init(mxX+2) ; r1.init(mxX+2) ; r2.init(mxX+2) ;

    cntRect = 0 ; cntPoint = 0 ;

    i64 ans = 0LL ;

    for(i=1 ; i<=n ; i++)
    {
        t = qType[i] ;

        if( t==1 )
        {
            cntPoint++ ;
            int x = point[cntPoint].x , y = point[cntPoint].y ;
        //    printf("%d %d\n",x,y) ;
            ans += r1.query( x, y ) - r2.query( x, y ) ;
            pt.add( x, y ) ;
        }
        else{
            cntRect++ ;
            int x1 = rect[cntRect].x1 , x2=rect[cntRect].x2 , y1=rect[cntRect].y1 , y2=rect[cntRect].y2 ;
      //      printf("%d %d %d %d\n",x1,y1,x2,y2) ;
            ans += pt.query(x2,y2)-pt.query(x1-1,y2) - pt.query(x2,y1-1)+pt.query(x1-1,y1-1) ;
            r1.add( x1,y1 ) ; r1.add( x2+1,y2+1 ) ;
            r2.add( x1,y2+1) ; r2.add(x2+1,y1) ;
        }
        printf("%lld\n",ans) ;
    }
    return 0 ;
}
/*
7
1 5 5
1 5 5
1 5 5
2 2 2 9 9
2 1 1 5 5
2 1 1 2 2
1 2 2
*/
