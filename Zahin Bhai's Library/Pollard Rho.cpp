#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

const long long LIM = LLONG_MAX;

long long mul(long long a, long long b, long long m){
    long long x, res;

    if (a < b) swap(a, b);
    if (!b) return 0;
    if (a < (LIM / b)) return ((a * b) % m);

    res = 0, x = (a % m);
    while (b){
        if (b & 1){
            res = res + x;
            if (res >= m) res -= m;
        }
        b >>= 1;
        x <<= 1;
        if (x >= m) x -= m;
    }

    return res;
}

long long expo(long long x, long long n, long long m){
    long long res = 1;

    while (n){
        if (n & 1) res = mul(res, x, m);
        x = mul(x, x, m);
        n >>= 1;
    }

    return (res % m);
}

const int small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 51, 53, 59, 61, 67, 71};

bool miller_rabin(long long p, int lim){
    long long a, s, m, x, y;
    s = p - 1, y = p - 1;
    while (!(s & 1)) s >>= 1;

    while (lim--){
        x = s;
        a = (rand() % y) + 1;
        m = expo(a, x, p);

        while ((x != y) && (m != 1) && (m != y)){
            m = mul(m, m, p);
            x <<= 1;
        }
        if ((m != y) && !(x & 1)) return false;
    }

    return true;
}

void brent_pollard_rho(uint64_t n, vector <uint64_t> &v){
    if (miller_rabin(n, 10)){
        v.push_back(n);
        return;
    }

    uint64_t a, g, x, y;
    y = 1;
    a = rand() % n;
    x = rand() % n;

    for (int i = 0; ((i * i) >> 1) < n; i++){
        x = mul(x, x, n);
        x += a;
        if (x < a) x += (ULLONG_MAX - n) + 1;
        x %= n;

        g = __gcd(n, y - x);
        if ((g != 1) && (g != n)){
            n /= g;
            brent_pollard_rho(g, v);
            if (n != g) brent_pollard_rho(n, v);
            else if (miller_rabin(n, 10)) v.push_back(n);
            return;
        }

        if (!(i & (i - 1))) y = x;
    }
    brent_pollard_rho(n, v);
}

void factorize(uint64_t n, vector <uint64_t> &v){
    srand(time(0));
    int i, j, x;

    for (i = 0; i < 21; i++){
        x = small_primes[i];
        while ((n % x) == 0){
            n /= x;
            v.push_back(x);
        }
    }

    if (n > 1) brent_pollard_rho(n, v);
    sort(v.begin(), v.end());
}

int main(){
    int i, t;
    uint64_t n, x;

    cin >> t;
    while (t--){
        cin >> n;
        vector <uint64_t> v;
        factorize(n, v);
        sort(v.begin(), v.end());

        v.push_back(-1);
        int len = v.size();
        int c = 0, counter = 0;

        printf("%llu = ", n);
        for (i = 0; (i + 1) < len; i++){
            if (v[i] == v[i + 1]) counter++;
            else{
                if (c) printf(" * ");
                if (counter) printf("%llu^%d", v[i], ++counter);
                else printf("%llu", v[i]);
                c++, counter = 0;
            }
        }
        puts("");
    }

    return 0;
}
