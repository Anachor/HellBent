#include <bits/stdc++.h>

using namespace std ;
typedef pair <int,int> pii ;
const long long N = 1e6 +5 , md = 1e9 + 7 ;

long long BigMod(long long b , long long p) {
    if (p == 0) return 1 ;
    if (p == 1) return b ;
    long long t = BigMod(b,p/2) ;
    t = (t*t) ;
    if (p&1) return (t*b) ;
    return t ;
}

long long rot (long long n , long long c) {  /// Sum of Fix(g) where g is a component of rotation set
    long long ans = 0 ;
    for (long long i = 0 ; i < n ; i++) {
        long long g = __gcd(n,i) ;
        ans = ans + BigMod(c,g) ;
    }
    return ans ;
}

long long reflection (long long n , long long c) {
    if (n&1) {
        return (n*BigMod(c,(n+1)/2)) ;
    }
    else {
        long long side = ((n/2)*BigMod(c,n/2)) ;
        long long vertex = ((n/2)*BigMod(c,n/2+1)) ;
        return (side + vertex) ;
    }
}

long long necklace(long long n,long long c) {
    long long ans = rot(n,c)/n ;
    return ans;
}

long long bracelet(long long n , long long c) {
    long long ans = rot(n,c) + reflection(n,c) ;
    ans = ans/(2*n);
    return ans ;
}

int main () {
    long long n ,c ;
    while (cin >> n >> c) {
        printf ("%lld %lld\n" , necklace(n,c) , bracelet(n,c)) ;
    }
    return 0;
}
