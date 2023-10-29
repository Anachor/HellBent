#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

///O(n^(3/4)/log). Runs in ~1.5 secs for N = 10^13
namespace PCF {
    const LL MAX = 1e13;
    const int N = 7e6;   ///around MAX^(2/3)/15
    const int M = 7, PM = 2*3*5*7*11*13*17;

    bool isp[N];
    int prime[N], pi[N];
    int phi[M+1][PM+1], sz[M+1];

    auto div = [](LL a, LL b) ->LL {return double(a)/b;};
    auto rt2 = [](LL x) -> int { return sqrtl(x); };
    auto rt3 = [](LL x) -> int { return cbrtl(x); };

    void init() {
        int cnt = 0;
        for (int i=2; i<N; i++) isp[i] = true;
        pi[0] = pi[1] = 0;
        for(int i=2; i<N; i++) {
            if(isp[i]) prime[++cnt] = i;
            pi[i] = cnt;
            for(int j=1; j<=cnt && i*prime[j]<N; j++) {
                isp[i * prime[j]] = false;
                if(i % prime[j] == 0)   break;
            }
        }
        sz[0] = 1;
        for(int i = 0; i <= PM; ++i)  phi[0][i] = i;
        for(int i = 1; i <= M; ++i) {
            sz[i] = prime[i] * sz[i - 1];
            for(int j = 1; j <= PM; ++j)
                phi[i][j] = phi[i-1][j] - phi[i-1][div(j,prime[i])];
        }
    }
    LL getphi(LL x, int s) {
        if(s == 0)  return x;
        if(s <= M)  return phi[s][x % sz[s]] + (x/sz[s]) * phi[s][sz[s]];
        if(x <= 1LL*prime[s]*prime[s])   return pi[x] - s + 1;
        if(x <= 1LL*prime[s]*prime[s]*prime[s] && x < N) {
            int s2x = pi[rt2(x)];
            LL ans = pi[x]-(s2x+s-2)*(s2x-s+1)/2;
            for(int i = s + 1; i <= s2x; ++i) ans += pi[div(x,prime[i])];
            return ans;
        }
        return getphi(x, s-1) - getphi(div(x,prime[s]), s-1);
    }
    LL getpi(LL x) {
        if(x < N)   return pi[x];
        LL ans = getphi(x, pi[rt3(x)]) + pi[rt3(x)] - 1;
        for(int i = pi[rt3(x)] + 1, ed = pi[rt2(x)]; i <= ed; ++i)
            ans -= getpi(div(x,prime[i])) - i + 1;
        return ans;
    }
}

///O(n^(3/4)). Runs in ~1.5 secs for N = 10^12
namespace PCFslow {
    auto f = [](LL n) { return 1; };   /// should be multiplicative
    auto pref = [](LL n) {return n;};  /// returns sum_{i=1..n} f(i)
    auto div = [](LL a, LL b) ->LL {return double(a)/b;};

    const LL MAX=1e12, N = 2*sqrt(MAX) + 100;
    LL ds[N], sf[N], k, sq, n, cnt;

    ///Valid for all n/i after solve(n) is called
    LL getpi (LL x) {
        if (x <= sq) return sf[x-1];
        else         return sf[cnt-div(n,x)];
    }

    /// Find sum(f(p)) over all primes p <= n
    LL solve(LL nn) {
        k = 1, cnt = 0, n = nn;
        while (k*k <= n)    ds[cnt++] = k++;
        sq = k-1;
        if (k*k == n) --k;
        while (--k)         ds[cnt++] = n/k;

        for (int i=0; i<cnt; i++)  sf[i] = pref(ds[i])-1;

        for (LL p=2; p*p <=n; ++p) {
            if (sf[p-1] == sf[p-2])     continue;
            LL sp = sf[p-2], p2 = p*p;
            for (int i = cnt-1; i>=0 && ds[i]>=p2; --i)
                sf[i] -= (getpi(div(ds[i],p))-sp) * f(p);
        }
        return sf[cnt-1];
    }
}
int main() {
  	PCF::init();
  	LL n = PCFslow::MAX;

  	cin>>n;
  	cout<<PCFslow::solve(n)<<endl;
}
