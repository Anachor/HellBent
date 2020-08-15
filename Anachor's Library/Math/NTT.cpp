/**
Iterative Implementation of Number Theoretic Transform
Complexity: O(N log N)
Slower than regular fft
Possible Optimizations:
1. Remove leading zeroes
2. Keep the mod const

Suggested mods (mod, root, inv, pw) :
7340033, 5, 4404020, 1<<20
13631489, 11799463,6244495, 1<<20
23068673, 177147,17187657, 1<<21
463470593, 428228038, 182429, 1<<21
415236097, 73362476, 247718523, 1<<22
918552577, 86995699, 324602258, 1<<22
998244353, 15311432, 469870224, 1<<23
167772161, 243, 114609789, 1<<25
469762049, 2187, 410692747, 1<<26
If required mod is not above, use nttdata function OFFLINE
**/

#include<bits/stdc++.h>
using namespace std;


namespace NTT {
    int N;
    vector<int> perm;
    vector<int>wp[2][30];
    const int mod = 998244353, root = 15311432, inv = 469870224, pw = 1<<23;

    int power(int a, int p) {
        if (p==0)   return 1;
        int ans = power(a, p/2);
        ans = (ans * 1LL * ans)%mod;
        if (p%2)    ans = (ans * 1LL * a)%mod;
        return ans;
    }

    void precalculate() {
        perm.resize(N);
        perm[0] = 0;

        for (int k=1; k<N; k<<=1) {
            for (int i=0; i<k; i++) {
                perm[i] <<= 1;
                perm[i+k] = 1 + perm[i];
            }
        }

        for (int b=0; b<2; b++) {
            for (int idx = 0, len = 2; len <= N; idx++, len <<= 1) {
                int factor = b ? inv : root;
                for (int i = len; i < pw; i <<= 1)
                    factor = (factor*1LL*factor)%mod;

                wp[b][idx].resize(N);
                wp[b][idx][0] = 1;
                for (int i = 1; i < len; i++) {
                    wp[b][idx][i] = (wp[b][idx][i-1]*1LL*factor)%mod;
                }
            }
        }
    }

    void fft(vector<int> &v, bool invert = false) {
        if (v.size() != perm.size()) {
            N = v.size();
            assert(N && (N&(N-1)) == 0);
            precalculate();
        }

        for (int i=0; i<N; i++)
            if (i < perm[i])
                swap(v[i], v[perm[i]]);

        for (int idx = 0, len = 2; len <= N; idx++, len <<= 1) {
            for (int i=0; i<N; i+=len) {
                for (int j=0; j<len/2; j++) {
                    int x = v[i+j];
                    int y = (wp[invert][idx][j]*1LL*v[i+j+len/2])%mod;
                    v[i+j] = (x+y>=mod ? x+y-mod : x+y);
                    v[i+j+len/2] = (x-y>=0 ? x-y : x-y+mod);
                }
            }
        }
        if (invert) {
            int n1 = power(N, mod-2);
            for (int &x : v) x = (x*1LL*n1)%mod;
        }
    }

    vector<int> multiply(vector<int> a, vector<int> b) {
        int n = 1;
        while (n < a.size()+ b.size())  n<<=1;
        a.resize(n);
        b.resize(n);

        fft(a);
        fft(b);
        for (int i=0; i<n; i++) a[i] = (a[i] * 1LL * b[i])%mod;
        fft(a, true);
        return a;
    }
};

const int M = 998244353, N = 2e6;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    srand(3423423);

    vector<int> a(N), b(N);
    long long asum = 0, bsum = 0, csum = 0;
    for (int i=0; i<N; i++) asum += (a[i] = rand()%M);
    for (int i=0; i<N; i++) bsum += (b[i] = rand()%M);

    vector<int> c = NTT::multiply(a, b);
    for (int x: c)   csum += x;

    cout<<csum<<endl;
}

int power(int a, int p, int mod) {
    if (p==0)   return 1;
    int ans = power(a, p/2, mod);
    ans = (ans * 1LL * ans)%mod;
    if (p%2)    ans = (ans * 1LL * a)%mod;
    return ans;
}


/** Find primitive root of p assuming p is prime.
if not, we must add calculation of phi(p)
*/

int primitive_root(int p) {
    if (p == 2) return 1;
    vector<int> factor;
    int phi = p-1,  n = phi;

    for (int i=2; i*i<=n; ++i)
        if (n%i == 0) {
            factor.push_back (i);
            while (n%i==0)  n/=i;
        }

    if (n>1)  factor.push_back(n);

    for (int res=2; res<=p; ++res) {
        bool ok = true;
        for (int i=0; i<factor.size() && ok; ++i)
            ok &= power(res, phi/factor[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}


/**
  Generates necessary info for NTT (for offline usage :3)
  returns maximum k such that 2^k divides mod
  ntt can only be applied for arrays not larger than this size
  mod MUST BE PRIME!!!!!
  We use that fact that primes the form p=c*2^k+1,
  there always exist the 2^k-th root of unity.
  It can be shown that g^c is such a 2^k-th root
  of unity, where g is a primitive root of p.
*/


int nttdata(int mod, int &root, int &inv, int &pw) {
    int c = 0, n = mod-1;
    while (n%2 == 0) c++, n/=2;
    pw = (mod-1)/n;
    int g = primitive_root(mod);
    root = power(g, n, mod);
    inv = power(root, mod-2, mod);
    return c;
}
