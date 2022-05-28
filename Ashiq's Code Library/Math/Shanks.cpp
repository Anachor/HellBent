#include <bits/stdc++.h>
using namespace std ;
const long long N = 105 , md = 100000007  , INF = md ;

long long bigmod (long long b ,long long p , long long M) {
    if (p == 0) return 1 ;
    if (p == 1) return b%M ;
    if (p&1) return (b*bigmod(b,p-1,M))%M ;
    long long t = bigmod(b,p/2,M) ;
    return (t*t)%M ;
}

long long Shanks(long long a , long long b , long long M) {    /// a^x = b (mod M)
    map <long long,long long> vals ;
    long long n = (long long)sqrt(M+.0) + 1 ;
    for (long long p = n ; p >= 1 ; p--) {
        vals[bigmod(a,(n*p)%M,M)] = p ;
    }
    long long ans = INF ;
    for (long long q = 0 ; q <= n ; q++) {
        long long cur = b*bigmod(a,q,M) ;
        cur %= M ;
        if (vals[cur]) {
            ans = min(ans,vals[cur]*n-q) ;
        }
    }
    return ans ;
}
