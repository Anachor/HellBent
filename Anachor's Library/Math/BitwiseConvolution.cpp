/**
Implementation of various bitwise convolutions.
Subset convo is O(2^K * K^2), rest are (2^K * K)
Author: anachor

**/

#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

vector<LL> XorTransform(vector<LL> p, bool inverse) {
    int n = p.size();
    assert((n&(n-1))==0);
    for (int len = 1; 2*len <= n; len <<= 1) {
        for (int i = 0; i < n; i += len+len) {
            for (int j = 0; j < len; j++) {
                LL u = p[i+j], v = p[i+len+j];
                if (!inverse)   p[i+j] = u+v, p[i+len+j] = u-v;
                else            p[i+j] = (u+v)/2, p[i+len+j] = (u-v)/2;
            }
        }
    }
    return p;
}

vector<LL> SOS(vector<LL> p, bool inverse, bool subset) {
    int k = __builtin_ctz(p.size());
    assert(p.size() == (1<<k));
    for (int i=0; i<k; i++)
        for (int mask=0; mask<(1<<k); mask++)
            if (bool(mask & (1<<i)) == subset) {
                if (!inverse) p[mask] += p[mask^(1<<i)];
                else          p[mask] -= p[mask^(1<<i)];
            }
    return p;
}

vector<LL> product(const vector<LL> &a, const vector<LL> &b) {
    assert(a.size() == b.size());
    vector<LL> ans(a.size());
    for (int i=0; i<a.size(); i++)  ans[i] = a[i] * b[i];
    return ans;
}

vector<LL> XorConvolution(vector<vector<LL>> vs) {
    int n = vs.size();
    for (int i=0; i<n; i++) vs[i] = XorTransform(vs[i], 0);
    vector<LL> ans = vs[0];
    for (int i=1; i<n; i++) ans = product(ans, vs[i]);

    ans = XorTransform(ans, 1);
    return ans;
}

vector<LL> ORConvolution(vector<vector<LL>> vs) {
    int n = vs.size();
    for (int i=0; i<n; i++) vs[i] = SOS(vs[i], 0, 1);

    vector<LL> ans = vs[0];
    for (int i=1; i<n; i++) ans = product(ans, vs[i]);
    ans = SOS(ans, 1, 1);
    return ans;
}

vector<LL> AndConvolution(vector<vector<LL>> vs) {
    int n = vs.size();
    for (int i=0; i<n; i++) vs[i] = SOS(vs[i], 0, 0);

    vector<LL> ans = vs[0];
    for (int i=1; i<n; i++) ans = product(ans, vs[i]);
    ans = SOS(ans, 1, 0);
    return ans;
}

vector<LL> SubsetConvolution(const vector<LL> &a, const vector<LL> &b) {
    int k = __builtin_ctz(a.size());
    assert(a.size() == (1<<k) && b.size() == (1<<k));

    vector<LL> Z(1<<k);
    vector<vector<LL>> A(k+1, Z), B(k+1, Z), C(k+1, Z);

    for (int mask=0; mask<(1<<k); mask++) {
        A[__builtin_popcount(mask)][mask] = a[mask];
        B[__builtin_popcount(mask)][mask] = b[mask];
    }

    for (int i=0; i<=k; i++) {
        A[i] = SOS(A[i], 0, 1);
        B[i] = SOS(B[i], 0, 1);
        for (int j=0; j<=i; j++)
            for (int mask = 0; mask < (1<<k); mask++)
                C[i][mask] += A[j][mask]*B[i-j][mask];
        C[i] = SOS(C[i], 1, 1);
    }

    vector<LL> ans(1<<k);
    for (int mask=0; mask<(1<<k); mask++) {
        ans[mask] = C[__builtin_popcount(mask)][mask];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<LL> S(1<<K), fib(1<<K);
    vector<LL> ab = SubsetConvolution(S, S), de = XorConvolution({S, S}), c = S;
    ab = product(ab, fib), c = product(c, fib), de = product(de, fib);
    vector<LL> ans = AndConvolution({ab, c, de});
}
