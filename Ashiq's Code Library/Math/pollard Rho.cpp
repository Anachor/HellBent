#include <bits/stdc++.h>
using namespace std;

bool mark[50000];
long long prime[10000], Pt = 0;
const long long LIM = LLONG_MAX, mod = 1e9 + 7;

void sieve() {
    prime[Pt++] = 2;
    int n = 47000;
    for(long long i = 3; i <= n; i++) {
        if(mark[i] == 0) {
            prime[Pt++] = i;
            for(long long j = i * i; j <= n; j += i) {
                mark[j] = 1;
            }
        }
    }
}

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

bool isPrime(long long n) {
    if (n == 2) return 1;
    if (n%2 == 0) return 0;
    long long d = n-1;
    while(d%2 == 0) d >>= 1;
    int test[] = {2,3,5,7,11,13,17,19,23};
    for(int i = 0; i < 9; i++) {
        long long x = test[i]%(n-2), temp = d;
        if (x < 2) x += 2;
        long long a = expo(x, d, n);
        while(temp != n-1 && a != 1 && a != n-1) {
            a = mul(a, a, n);
            temp <<= 1;
        }
        if (a != n-1 && (temp&1) == 0) return 0;
    }
    return 1;
}

long long pollard_rho(long long n, long long c) {
    long long x = 2, y = 2, i = 1, k = 2, d;
    while(true) {
        x = (mul(x, x, n) + c);
        if (x >= n) x -= n;
        d = __gcd(abs(x-y),n);
        if (d > 1) return d;
        if (++i == k) {
            y = x, k <<= 1;
        }
    }
    return n;
}

void llfactorize(long long n, vector<long long> &f) {
    if (n == 1) return;
    if (n < 1e9) {
        for(int i = 0; prime[i]* prime[i] <= n; i++) {
            while(n%prime[i] == 0) {
                f.push_back(prime[i]);
                n /= prime[i];
            }
        }
        if (n != 1) f.push_back(n);
        return;
    }
    if (isPrime(n)) {
        f.push_back(n);
        return;
    }
    long long d = n;
    for(int i = 2; d == n; i++){
        d = pollard_rho(n, i);
    }
    llfactorize(d, f);
    llfactorize(n/d, f);
}

void factorize(long long n, vector<pair<long long,long long>> &ans) {
    vector<long long> v;
    llfactorize(n, v);
    sort(v.begin(), v.end());
    long long a = v[0], b = 1;
    for(int i = 1; i < v.size(); i++) {
        if (v[i] == v[i-1] ) b++;
        else {
            ans.push_back({a,b});
            a = v[i];
            b = 1;
        }
    }
    ans.push_back({a,b});
}


int main() {

    sieve();
    while(true) {
        long long n;
        cin >> n;
        vector<pair<long long,long long>> f;
        factorize(n, f);
        for(int i = 0; i < f.size(); i++) {
            cout << f[i].first << " " << f[i].second << endl;
        }
    }
    return 0;
}
