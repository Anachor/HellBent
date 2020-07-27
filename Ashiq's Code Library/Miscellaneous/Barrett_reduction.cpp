// http://www.usaco.org/index.php?page=viewproblem2&cpid=1045

#include <bits/stdc++.h>
using namespace std;


typedef unsigned long long ull;

struct FastMod {
	ull b, m;
	FastMod(ull b) : b(b), m(-1ULL / b) {}
	ull reduce(ull a) { // a % b + (0 or b)
		return a - (ull)((__uint128_t(m) * a) >> 64) * b;
	}
};


const int N = 7505;
FastMod F(2);

int n, mod;
int C[N][N];
int fact[N];

void init() {
    C[0][0] = 1;
    for(int i = 1; i < N; i++) {
        C[i][0] = C[i][i] = 1;
        for(int j = 1; j < i; j++) {
            C[i][j] = (C[i-1][j]+C[i-1][j-1])%mod;
        }
    }
    fact[0] = 1;
    for(int i = 1; i < N; i++) {
        fact[i] = 1ll*i*fact[i-1]%mod;
    }
}

int bigmod(int b, int p, int m) {
    if(p == 0) return 1%m;
    int t = bigmod(b, p/2, m);
    t = 1ll*t*t%m;
    if(p & 1) return 1ll*b*t%m;
    return t;
}

int main() {
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> mod;
    mod--;
    F = FastMod(mod);
    init();
    int ans = 1;
    vector<bool> composite(n+1);
    composite[1] = true;
    for(int i = 2; i <= n; i++) {
        if(composite[i]) continue;
        for(int j = i+i; j <= n; j += i) composite[j] = true;
        int contr = 0;
        for(int x = i; x <= n; x *= i) {
            int lim = n/x;
            vector<int> dp(lim+1), wo(lim+1);
            wo[0] = 1;
            for(int k = 1; k <= lim; k++) {
                for(int l = 1; l <= k; l++) {
                    int ways = F.reduce(1ll*wo[k-l]*C[k*x-1][l*x-1]);
                    ways = F.reduce(1ll*ways*fact[l*x-1]);
                    wo[k] += ways;
                    if(wo[k] >= mod) wo[k] -= mod;
                }
            }
            for(int k = lim; k >= 0; k--) {
                dp[k] = fact[n-k*x];
                int sub = 0;
                for(int l = k+1; l <= lim; l++) {
                    int ways = F.reduce(1ll*dp[l]*C[n-k*x][(l-k)*x]);
                    ways = F.reduce(1ll*ways*wo[l-k]);
                    sub += ways;
                    if(sub >= mod) sub -= mod;
                }
                dp[k] -= sub;
                if(dp[k] < 0) dp[k] += mod;
            }
            int c = fact[n]-dp[0];
            if(c < 0) c += mod;
            contr += c;
            if(contr >= mod) contr -= mod;
        }
        ans = 1ll*ans*bigmod(i, contr, mod+1)%(mod+1);
    }
    cout << ans << endl;

    return 0;
}

