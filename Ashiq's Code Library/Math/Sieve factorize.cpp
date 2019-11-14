#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
typedef vector <pair<int,int>> vii;

int np[N], phi[N];
vector<int> primes;

void sieve(int n) {
    for (int i = 1; i <= n; i++) phi[i] = i;
    np[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (np[i]) continue;
        primes.push_back(i);
        phi[i] = i-1;
        for (int j = 2*i; j <= n; j+=i) {
            np[j] = 1;
            phi[j] = (phi[j]/i)*(i-1);
        }
    }
}

vii factorize (int x) {
    vii v;
    for (int i = 0; primes[i]*primes[i] <= x; i++) {
        int k = 0;
        while (x%primes[i] == 0) {
            k++;
            x /= primes[i];
        }
        if (k) v.push_back(make_pair(primes[i],k));
    }
    if (x > 1) v.push_back(make_pair(x,1));
    return v;
}

int main () {
    int n = 1e5;
    sieve(n);
}
