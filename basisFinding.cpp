#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define PI ( acos(-1.0) )
#define IN freopen("dichromatic.in","r",stdin)
#define OUT freopen("dichromatic.out","w",stdout)
#define FOR(i,a,b) for(i=a ; i<=b ; i++)
#define DBG pf("Hi\n")
#define INF 1000000000
#define i64 long long int
#define eps (1e-8)
#define xx first
#define yy second
#define sq(x)  ((x)*(x))

using namespace __gnu_pbds;
using namespace std ;

#define maxn 200005

int bit[(1<<18)+5] ;

vector <int> Generate( int x )
{
    vector <int> vec ;
    vector <int> res ;
    vec.pb(0) ;
    vec.pb(1) ;

    for(int i=1 ; i<x ; i++)
    {
        int j = (1<<i) - 1 ;
        for( ; j>=0 ; j--)
        {
            vec.pb( (vec[j]|(1<<i)) ) ;
        }
    }
    for( int i=1 ; i<(1<<x) ; i++ )
    {
        res.pb( bit[ vec[i]^vec[i-1] ] ) ;
    }
    return res ;
}

int a[maxn] ;

/*
given some numbers in range [0 to 2^x), this function will return you with a set of basis
vectors from this numbers
*/
vector <int> findBasis( vector <int> b , int x )
{
    vector <int> idx , num ;
    for(int i=0 ; i<b.size() ; i++) idx.pb(i) , num.pb(b[i]) ;

    for(int i=x-1 , j=0 ; i>=0 ; i--,j++)
    {
        for(int k= j+1 ; k<idx.size() ; k++)
        {
            if( b[k] > b[j] )
            {
                swap(b[k],b[j]) ;
                swap(idx[k],idx[j]) ;
            }
        }
        for(int k=j+1 ; k<idx.size() ; k++)
        {
            if( (b[k]^b[j]) < b[k] ) b[k] ^= b[j] ;
        }

    }
    int i = (int)idx.size() - 1 ;
    while( i > 0 && b[i] == 0 )
    {
        b.pop_back() ;
        idx.pop_back() ;
        i-- ;
    }
    vector <int> basis ;
    for(int i=0 ; i<idx.size() ; i++) basis.pb( num[idx[i]] ) ;
    return basis ;
}

//

const int ln = 18 ;

int main()
{
    for(int i=0 ; i<=ln ; i++) bit[(1<<i)] = i ;
    int n ;
    scanf("%d",&n) ;

    for(int i=0; i<n ; i++ )
    {
        scanf("%d",&a[i]) ;
    }

    vector <int> ans ;
    ans.pb(0) ;

    for(int i=ln ; i>=1 ; i-- )
    {
        vector <int> b ;
        for(int j=0 ; j<n ; j++) if( a[j] < (1<<i) ) b.pb(a[j]) ;
        vector <int> basis = findBasis(b,i) ;
        if( (int)basis.size() == i )
        {
            vector <int> res = Generate(i) ;
            for(int j=0 ; j<res.size() ; j++) ans.pb( ans.back()^basis[ res[j]  ] ) ;
            break ;
        }
    }

    printf("%d\n",bit[(int)ans.size()]) ;
    for(int i=0 ; i<ans.size() ; i++)
    {
        printf("%d ",ans[i]) ;
    }

    return 0 ;
}
