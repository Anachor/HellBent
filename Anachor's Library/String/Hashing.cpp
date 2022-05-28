/**+
Simple Library for String Hashing, Uses Double Hash.
Hash(abc........z) = a*p^n + b*p^(n-1) + ...... + z

In order to convert to Single Hash -
    o Delete operator overloads and fix reduce()
    o Replace all PLL with LL
    o Change mp pairs to appropriate value
Or set M2 = 1, which should be nearly as fast.

Some Primes:
1000000007, 1000000009, 1000000861, 1000099999      ( < 2^30 )
1088888881, 1111211111, 1500000001, 1481481481      ( < 2^31 )
2147483647 (2^31-1),

Author: anachor

**/


#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PLL;

namespace Hashing {
    #define ff first
    #define ss second

    const PLL M = {1e9+7, 1e9+9};        ///Should be large primes
    const LL base = 1259;                ///Should be larger than alphabet size
    const int N = 1e6+7;                 ///Highest length of string

    PLL operator+ (const PLL& a, LL x)     {return {a.ff + x, a.ss + x};}
    PLL operator- (const PLL& a, LL x)     {return {a.ff - x, a.ss - x};}
    PLL operator* (const PLL& a, LL x)     {return {a.ff * x, a.ss * x};}
    PLL operator+ (const PLL& a, PLL x)    {return {a.ff + x.ff, a.ss + x.ss};}
    PLL operator- (const PLL& a, PLL x)    {return {a.ff - x.ff, a.ss - x.ss};}
    PLL operator* (const PLL& a, PLL x)    {return {a.ff * x.ff, a.ss * x.ss};}
    PLL operator% (const PLL& a, PLL m)    {return {a.ff % m.ff, a.ss % m.ss};}
    ostream& operator<<(ostream& os, PLL hash) {
        return os<<"("<<hash.ff<<", "<<hash.ss<<")";
    }
    PLL pb[N];      ///powers of base mod M

    ///Call pre before everything
    void hashPre() {
        pb[0] = {1,1};
        for (int i=1; i<N; i++)     pb[i] = (pb[i-1] * base)%M;
    }

    ///Calculates hashes of all prefixes of s including empty prefix
    vector<PLL> hashList(string s) {
        int n = s.size();
        vector<PLL> ans(n+1);
        ans[0] = {0,0};
        for (int i=1; i<=n; i++)    ans[i] = (ans[i-1] * base + s[i-1])%M;
        return ans;
    }

    ///Calculates hash of substring s[l..r] (1 indexed)
    PLL substringHash(const vector<PLL> &hashlist, int l, int r) {
        return (hashlist[r]+(M-hashlist[l-1])*pb[r-l+1])%M;
    }

    ///Calculates Hash of a string
    PLL Hash (string s) {
        PLL ans = {0,0};
        for (int i=0; i<s.size(); i++)  ans=(ans*base + s[i])%M;
        return ans;
    }

    ///Tested on https://toph.co/p/palindromist
    ///appends c to string
    PLL append(PLL cur, char c) {
        return (cur*base + c)%M;
    }

    ///Tested on https://toph.co/p/palindromist
    ///prepends c to string with size k
    PLL prepend(PLL cur, int k, char c) {
        return (pb[k]*c + cur)%M;
    }

    ///Tested on https://toph.co/p/chikongunia
    ///replaces the i-th (0-indexed) character from right from a to b;
    PLL replace(PLL cur, int i, char a, char b) {
        return cur + pb[i] * (M+b-a)%M;
    }

    ///Erases c from front of the string with size len
    PLL pop_front(PLL hash, int len, char c) {
        return (hash + pb[len-1]*(M-c))%M;
    }

    ///Tested on https://toph.co/p/palindromist
    ///concatenates two strings where length of the right is k
    PLL concat(PLL left, PLL right, int k) {
        return (left*pb[k] + right)%M;
    }

    PLL power (const PLL& a, LL p) {
        if (p==0)   return {1,1};
        PLL ans = power(a, p/2);
        ans = (ans * ans)%M;
        if (p%2)    ans = (ans*a)%M;
        return ans;
    }

    PLL inverse(PLL a)  {
        if (M.ss == 1)  return power(a, M.ff-2);
        return power(a, (M.ff-1)*(M.ss-1)-1);
    }

    ///Erases c from the back of the string
    PLL invb = inverse({base, base});
    PLL pop_back(PLL hash, char c) {
        return ((hash-c+M)*invb)%M;
    }

    ///Tested on https://toph.co/p/palindromist
    ///Calculates hash of string with size len repeated cnt times
    ///This is O(log n). For O(1), pre-calculate inverses
    PLL repeat(PLL hash, int len, LL cnt) {
        PLL mul = ((pb[len*cnt]-1+M) * inverse(pb[len]-1+M))%M;
        PLL ans = (hash*mul);
        if (pb[len].ff == 1)    ans.ff = hash.ff*cnt;
        if (pb[len].ss == 1)    ans.ss = hash.ss*cnt;
        return ans%M;
    }
}

/// Solves https://judge.yosupo.jp/problem/enumerate_palindromes
using namespace Hashing;
vector<PLL> forwardHash, backwardHash;
int n;
bool check(int l, int r) {
    return substringHash(forwardHash, l, r) == substringHash(backwardHash, n+1-r, n+1-l);
}

int main() {
    hashPre();

    string s;
    cin>>s;
    n = s.size();
    forwardHash = hashList(s);

    reverse(s.begin(), s.end());
    backwardHash = hashList(s);

    for (int i=0; i<2*n-1; i++) {
        int a = (i+1)/2, b = i/2+2;
        int lo = 0, hi = min(a, n+1-b);
        while (lo < hi) {
            int m = (lo + hi + 1)/2;
            if (check(a-m+1, b+m-1))    lo = m;
            else                        hi = m-1;
        }

        cout<<2*lo+(i%2==0)<<" ";
    }
}
