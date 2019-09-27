#include <bits/stdtr1c++.h>

#define MOD 1000000007
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

/*** Fast Doubling Algorithm to calculate n'th fibonacci number ***/
/*** fib(0) = 0, fib(1) = 1, fib(n) = fib(n - 1) + fib(n - 2) ***/

/// Recursive version (Faster, at least in SPOJ)

int fib(int& x, int& y, long long n){
    if (!n) x = 0, y = 1;
    else{
        int c, d;
        fib(c, d, n >> 1);
        long long a = c, b = d, z = (d << 1) - c;
        if (z < 0) z += MOD;

        x = (a * z) % MOD;
        y = ((a * a) + (b * b)) % MOD;

        if (n & 1){
            x += y;
            if (x >= MOD) x -= MOD;
            swap(x, y);
        }
    }
    return x;
}

int fib(long long n){
    int x = 0, y = 1;
    return fib(x, y, n);
}

/// Iterative version

int fib(long long n){
    long long a = 0, b = 1, d;

    for (int i = 63 - __builtin_clzll(n); i >= 0; i--){
        d = (b << 1) - a;
        if (d < 0) d += MOD;

        d = (a * d) % MOD;
        b = ((a * a) + (b * b)) % MOD, a = d;
        if ((n >> i) & 1){
            d = a + b;
            if (d >= MOD) d -= MOD;
            a = b, b = d;
        }
    }

    return a;
}

int main(){
    int n;
    while (cin >> n) cout << fib(n) << endl;
}
