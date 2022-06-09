///  Source: folklore, AlphaQ(Find Factor) 


#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;

namespace Rho {
    ULL mult(ULL a, ULL b, ULL mod) {
        LL ret = a * b - mod * (ULL)(1.0L / mod * a * b);
        return ret + mod * (ret < 0) - mod * (ret >= (LL) mod);
    }

    ULL power(ULL x, ULL p, ULL mod){
        ULL s=1, m=x;
        while(p) {
            if(p&1) s = mult(s, m, mod);
            p>>=1;
            m = mult(m, m, mod);
        }
        return s;
    }

    vector<LL> bases = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    bool isprime(LL n) {
        if (n<2)    return 0;
        if (n%2==0)   return n==2;

        ULL s = __builtin_ctzll(n-1), d = n>>s;
        for (ULL x: bases) {
            ULL p = power(x%n, d, n), t = s;
            while (p!=1 && p!=n-1 && x%n && t--) p = mult(p, p, n);
            if (p!=n-1 && t != s)               return 0;
        }
        return 1;
    }

    ///Returns a proper divisor if n is composite, n otherwise
    ///Possible Optimization: use binary gcd for ~10% speedup
    mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
    ULL FindFactor(ULL n) {
        if (n == 1 || isprime(n))    return n;
        ULL c = 1, x = 0, y = 0, t = 0, prod = 2, x0 = 1, q;
        auto f = [&](ULL X) { return mult(X, X, n) + c;};

        while (t++ % 128 or gcd(prod, n) == 1) {
            if (x == y) c = rng()%(n-1)+1, x = x0, y = f(x);
            if ((q = mult(prod, max(x, y) - min(x, y), n))) prod = q;
            x = f(x), y = f(f(y));
        }
        return gcd(prod, n);
    }

    ///Returns all prime factors
    vector<ULL> factorize(ULL x) {
        if (x == 1)     return {};
        ULL a = FindFactor(x), b = x/a;
        if (a == x) return {a};
        vector<ULL> L = factorize(a), R = factorize(b);
        L.insert(L.end(), R.begin(), R.end());
        return L;
    }
}

///Solves https://judge.yosupo.jp/problem/factorize

int main() {
    int q;
    cin>>q;

    while (q--) {
        long long x;
        cin>>x;
        vector<ULL> ans = Rho::factorize(x);
        sort(ans.begin(), ans.end());
        cout<<ans.size();
        for (LL x: ans)    cout<<" "<<x;
        cout<<endl;
    }
}
