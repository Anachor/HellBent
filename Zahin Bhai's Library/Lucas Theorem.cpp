#include <bits/stdtr1c++.h>

#define MAXP 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

/// Lucas theorem to calculate binomial co-efficients modulo a prime

namespace lc{
    int MOD = 1000000007;
    int fact[MAXP], inv[MAXP];

    /// Call once with the modulo prime
    void init(int prime){
        MOD = prime;
        fact[0] = 1, inv[MOD - 1] = MOD - 1;
        for (int i = 1; i < MOD; i++) fact[i] = ((long long)fact[i - 1] * i) % MOD;
        for (int i = MOD - 2; i >= 0; i--) inv[i] = ((long long)inv[i + 1] * (i + 1)) % MOD;
    }

    inline int count(int n, int k){
        if (k > n) return 0;
        int x = ((long long)inv[n - k] * inv[k]) % MOD;
        return ((long long)x * fact[n]) % MOD;
    }

    /// Lucas theorem, calculates binomial(n, k) modulo MOD, MOD must be a prime
    inline int binomial(long long n, long long k){
        if (k > n) return 0;

        int res = 1;
        k = min(k, n - k);
        while (k && res){
            res = ((long long)res * count(n % MOD, k % MOD)) % MOD;
            n /= MOD, k /= MOD;
        }
        return res;
    }

    /*** Alternate and extended functionalities ***/

    /// Must call init with prime before (Or set lc::MOD = prime)
    /// Computes (n! / (p ^ (n / p))) % p in O(p log(n)) time, p MUST be a prime
    /// That is, calculating n! without p's powers
    /// For instance factmod(9, 3) = (1 * 2 * 4 * 5 * 2 * 7 * 8 * 1) % 3 = 1
    inline int factmod(long long n, int p){
        int i, res = 1;
        while (n > 1) {
            if ((n / p) & 1) res = ((long long)res * (p - 1)) % p;
            for (i = n % p; i > 1; i--) res = ((long long)res * i) % p;
            n /= p;
        }
        return (res % p);
    }

    inline int expo(int a, int b){
        int res = 1;

        while (b){
            if (b & 1) res = (long long)res * a % MOD;
            a = (long long)a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    /// Trailing zeros of n! in base p, p is a prime
    inline long long fact_ctz(long long n, long long p){
        long long x = p, res = 0;
        while (n >= x){
            res += (n / x);
            x *= p;
        }
        return res;
    }

    /// Calculates binomial(n, k) modulo MOD, MOD must be a prime
    inline int binomial2(long long n, long long k){
        if (k > n) return 0;
        if (fact_ctz(n, MOD) != (fact_ctz(k, MOD) + fact_ctz(n - k, MOD))) return 0;
        int a = factmod(n - k, MOD), b = factmod(k, MOD), c = factmod(n, MOD);
        int x = ((long long)expo(a, MOD - 2) * expo(b, MOD - 2)) % MOD;
        return ((long long)x * c) % MOD;
    }
}

int main(){
    lc::init(997);
    printf("%d\n", lc::binomial(10, 5));
    printf("%d\n", lc::binomial(1996, 998));

    lc::MOD = 10007;
    printf("%d\n", lc::binomial2(10, 5));
    printf("%d\n", lc::binomial2(1996, 998));
    return 0;
}
