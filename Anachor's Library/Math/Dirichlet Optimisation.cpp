/**
    Let h = f*g and sf, sg and sh be sums of f, g, h resp.
    If we can calculate values of sg and sh quickly, we can then calculate
    sf(n) quickly using the following formula and the harmonic lemma.

    sf(n) = (sh(n) - sum{2...n} sf(n/d) g(d)) / g(1).

    Complexity: O(n^(2/3))
    Usage: Call precal(), then call solve()

    Author: anachor

    Practice Problems:
        https://www.hackerrank.com/contests/projecteuler/challenges/euler228/problem
        https://projecteuler.net/problem=512

*/

#include<bits/stdc++.h>
using namespace std;

///Calculates sum(mu(n)), Here, g = 1, f = mu(n), h = is1(n)
typedef long long T;
typedef long long LL;
namespace Dirichlet {
    const int RT = 5e7;    ///RT ~ max^(2/3)
    T pre[RT];

    void precal() {    ///1. pre-calculate pre[i] = sf(i) for i < RT
        vector<int> lp(RT), pr;

        pre[1] = 1;
        for (int i=2; i<RT; ++i) {
            if (lp[i] == 0) {
                lp[i] = i;
                pr.push_back (i);
            }
            for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<RT; ++j)
                lp[i * pr[j]] = pr[j];

            int z = i/lp[i];
            if (lp[z] == lp[i])     pre[i] = 0;
            else                    pre[i] = pre[z]*-1;
        }

        for (int i=1; i<RT; i++)     pre[i] += pre[i-1];
    }

    auto sg = [](LL n) { return n; };   /// 2. returns sum{i=1..n} g(i)
    auto sh = [](LL n) { return 1; };   /// 3. returns sum{i=1..n} h(i)

    unordered_map<long long, T> mem;
    T solve(long long x) {
        if (x < RT)     return pre[x];
        if (mem.count(x))     return mem[x];

        T ans = sh(x);
        for (long long i=1, last=x; i*i<=x; i++) {
            long long l=i, r=i, inv=last;
            if (i > 1)     ans = (ans - (sg(r)-sg(l-1))*solve(inv));
            l=x/(i+1)+1, r=last, inv=i;
            if (last != i) ans = (ans - (sg(r)-sg(l-1))*solve(inv));
            last = l-1;
        }

        return mem[x] = ans;
    }
}

int main() {
    Dirichlet::precal();
    cout<<Dirichlet::solve(1e12)<<endl;
}
