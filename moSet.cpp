/*
CF-375D
A undirected tree is given, each node having a colour , we'll have some queries of form (v,k).
We've to answer how many color occurs at least k'times in the subtree rooted at v.
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
#define IN freopen("nocross.in","r",stdin)
#define OUT freopen("nocross.out","w",stdout)
#define FOR(i,a,b) for(i=a ; i<=b ; i++)
#define DBG pf("Hi\n")
#define INF 1000000001
#define i64 long long int
#define eps (1e-8)
#define xx first
#define yy second
#define ln 17
#define off 2
#define sq(x) ((x)*(x))

using namespace __gnu_pbds;
using namespace std ;

typedef pair< i64,i64 > pii ;
typedef tree< i64, null_type, less<i64>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

/* Special functions:

        find_by_order(k) --> returns iterator to the kth largest element counting from 0
        order_of_key(val) --> returns the number of items in a set that are strictly smaller than our item
*/

#define maxn 100005

class moSet{

    /*
    intution
    say, now I have my cnt array like this cnt[] = { 0 , 4 , 1 , 2 , 3 , 4, 0 , 2 }
    and each time cnt changes by only one, so if a element occurred 2 times before, now it's
    occurrence can be either 1 or 3. And each time we want to know, how many element occurred
    at least k times. Then we can keep our cnt[] array in another form by sorting the occurrence.
    occ[] = { 0,0,1,2,2,3,4,4 }. So when an increase an elements occurrence , say previously an element
    occurred 2 times, now it is occurring 3 times , then there will be only a slight change in occ array,
    one 2 will be just turned into 3.

     Description of the data structure
     this is a data-structure mainly for keeping track of occurrences
     lets say currently we have n=6 and our sortedArray[] = {0,0,1,2,2,3,4,4}
     if we increase(2) , then sortedArray[] = { 0,0,1,2,3,3,4,4 } , so one 2 will be turned  into 3
     if we decrease(3) now ,then sortedArray[] = { 0,0,1,2,2,3,4,4 } , so one 3 will be turned  into 2
     along with this we've start , and en array and exist array, start[1] = 2 , en[2] = 4 , exist[1] = true,
     exist[5] = false, also remember here we can only handle elements from 0 to n (inclusive)
    */
public:
    bool *exist ;
    int *sortedArray, *Start , *End , n ;

    moSet(int _n)
    {
        n = _n ;
        exist = new bool[n+2] ;
        sortedArray = new int[n+2] ;
        Start = new int[n+2] ;
        End = new int[n+2] ;

        for(int i=0 ; i<=n ; i++) exist[i] = false ;
    }
    moSet( int _n , int initVal )
    {
        n = _n ;
        exist = new bool[n+2] ;
        sortedArray = new int[n+2] ;
        Start = new int[n+2] ;
        End = new int[n+2] ;

        for(int i=0 ; i<=n ; i++) exist[i] = false ;
        exist[initVal] = true ;
        for(int i=0 ; i<=n ; i++) sortedArray[i] = initVal ;
        Start[initVal] = 0 ; End[initVal] = n ;
    }

    void increase(int v)
    {
        if(!exist[v] || v<0 || v>=n ) return ; // 0 to n-1
        sortedArray[ End[v] ] = v+1 ;
        if( !exist[v+1] )
        {
            exist[v+1] = true ;
            Start[ v+1 ] = End[v+1] = End[v] ;
        }
        else Start[v+1]-- ;
        End[v]-- ;
        if(Start[v]>End[v]) exist[v] = false ;
        return ;
    }
    void decrease(int v)
    {
        if( !exist[v] || v<=0 || v>n ) return ; // 1 to n
        sortedArray[ Start[v] ] = v-1 ;
        if( !exist[v-1] )
        {
            exist[v-1] = true ;
            Start[v-1] = End[v-1] = Start[v] ;
        }
        else End[v-1]++ ;
        Start[v]++ ;
        if(Start[v]>End[v]) exist[v] = false ;
        return ;
    }

    int howMany(int x)
    {
        if( sortedArray[n] <x ) return 0 ;
        int lo = 0 , hi = n ;
        while(lo<hi)
        {
            int mid = (lo+hi)/2;
            if( sortedArray[mid]>=x ) hi = mid ;
            else lo = mid+1 ;
        }
        return n-lo+1 ;
    }

};


int posInArray[maxn] , endPos[maxn] , Time , s ;
int c[maxn] , col[maxn] , cnt[maxn] , ans[maxn] ;
vector <int> g[maxn] ;

void dfs(int u , int par)
{
    posInArray[u] = ++Time ;
    col[Time] = c[u] ;
    for(int i=0 ; i<g[u].size() ; i++ )
    {
        int v = g[u][i] ;
        if(v==par) continue ;
        dfs(v,u) ;
    }
    endPos[u] = Time ;
}

struct Query{
    int l ,r ,id , k ;
}query[maxn];

bool moComp( Query q1 , Query  q2 )
{
    if( q1.l/s == q2.l/s ) return q1.r<q2.r ;
    return q1.l<q2.l ;
}

int main()
{
    int i , j , k , m , n , l , r ;

    scanf("%d %d",&n,&m) ;

    moSet mySet(n,0) ;
/*
    while(1)
    {
        scanf("%d %d",&k,&l) ;
        if( k==1 ) mySet.increase(l) ;
        else mySet.decrease(l) ;
        for(i=0 ; i<=10 ; i++) printf("%d ",mySet.sortedArray[i]) ;
        printf("\n") ;
    }
*/
    for(i=1 ; i<=n ; i++) scanf("%d",&c[i]) ;

    for(i=1 ; i<n ; i++)
    {
        int u , v ;
        scanf("%d %d",&u,&v) ;
        g[u].pb(v) ; g[v].pb(u) ;
    }
    Time = 0 ;
    dfs(1,-1) ;

    for(i=1 ; i<=m ; i++)
    {
        int v ;
        scanf("%d %d",&v,&k) ;
        query[i].l = posInArray[v] ; query[i].r = endPos[v] ; query[i].k = k ;
        query[i].id = i ;
    }

    s = sqrt(n+0.0) + 1 ;

    sort(query+1, query+m+1,moComp) ;

    memset(cnt,0,sizeof(cnt)) ;

    l = 1 ; r = 0 ;

    for(i=1 ; i<=m ; i++)
    {
      //  printf("%d %d")
        while(r<query[i].r)
        {
            r++ ;
            j = r ;
            mySet.increase( cnt[ col[j] ] ) ;
            cnt[ col[j] ]++ ;
        }
        while(l>query[i].l)
        {
            l-- ;
            j = l ;
            mySet.increase( cnt[ col[j] ] ) ;
            cnt[ col[j] ]++ ;
        }
        while(r>query[i].r)
        {
            j = r ;
            mySet.decrease(cnt[col[j]]) ;
            cnt[ col[j] ]-- ;
            r-- ;
        }
        while(l<query[i].l)
        {
            j = l ;
            mySet.decrease(cnt[col[j]]) ;
            cnt[ col[j] ]-- ;
            l++ ;
        }
        ans[ query[i].id ] = mySet.howMany(query[i].k) ;
   /*     printf("%d\n",query[i].id) ;
        for(j=0 ; j<=n ; j++) printf("%d ",mySet.sortedArray[j]) ;
        printf("\n") ; */
    }

    for(i=1 ; i<=m ; i++) printf("%d\n", ans[i] ) ;

    return 0 ;
}
/*
10 10
82 48 59 48 32 83 34 46 47 79
2 1
3 1
4 3
5 4
6 1
7 2
8 3
9 2
10 2
1 2
1 1
1 3
1 5
2 1
2 2
3 1
3 3
6 1
9 2
*/
