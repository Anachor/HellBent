#include <bits/stdc++.h>
using namespace std;

bitset <100> bs ;

int main () {
    /// lowest set bit of a 32-bit integer : example : __builtin_ctz(100100) = 2 . exception : builtin_ctz(0) is undefined
    ///long long x = 8589934591 ;
    ///cout << __builtin_ctz(x) << endl ;
    /// lowest set bit of a 64-bit integer : example : __builtin_ctzll(100100) = 2 . exception : builtin_ctzll(0) is undefined
    ///__builtin_ctzll
    /// number of set bits : __builtin_popcount(x)
    /// number of set bits : __builtin_popcountll(x)

    bs[15] = 1 ;
    bs[43] = 1 ;
    bs[12] = 1 ;
    cout << bs._Find_first() << endl ; /// first set bit : prints 12 /// returns bs.size() if no set bit
    cout << bs._Find_next(15) << endl ; /// set bit strictly next to 15 . prints 43 /// if no set bit after idx = (15) returns bs.size()
    cout << bs.count() << endl ;
    //bs.set() ;
    //bs.reset() ;
    bs.flip() ;
    cout << bs.count() << endl ;
}
