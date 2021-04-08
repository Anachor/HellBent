#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL, LL>  PLL;

namespace ArrayPartitionDP {
    PLL operator + (const PLL &a, const PLL &b) {
        return PLL(a.first+b.first, a.second+b.second);
    }

    ///Solves dp[i] = min(dp[j] + cost(j+1, i)) given that cost() is QF
    PLL solve1D(int n, PLL cost(int, int)) {
        vector<PLL> dp(n+1);
        vector<int> opt(n+1);
        deque<pair<int, int>> dq;
        dq.push_back({0, 1});
        dp[0] = {0, 0};

        for (int i=1; i<=n; i++) {
            opt[i] = dq.front().first;
            dp[i] = dp[opt[i]] + cost(opt[i]+1, i);
            if (i == n) break;

            dq[0].second++;
            if (dq.size() > 1 && dq[0].second == dq[1].second)  dq.pop_front();

            int en = n;
            while(dq.size()) {
                int o = dq.back().first, st = dq.back().second;
                if (dp[o]+cost(o+1, st) >= dp[i]+cost(i+1, st))  dq.pop_back();
                else {
                    int lo = st, hi = en;
                    while (lo < hi) {
                        int mid = (lo+hi+1)/2;
                        if (dp[o]+cost(o+1, mid) < dp[i]+cost(i+1, mid) )   lo = mid;
                        else                                                hi = mid-1;
                    }
                    if (lo < n) dq.push_back({i, lo+1});
                    break;
                }
                en = st-1;
            }
            if (dq.empty()) dq.push_back({i, i+1});
        }
        return dp[n];
    }

    function<LL(int, int)> base_cost;
    long long C;
    int n;

    PLL cost(int l, int r) {
        return {base_cost(l, r)+C, 1};
    }

    PLL check(long long c) {
        C = c;
        return solve1D(n, cost);
    }

    long long solve(int N, int k, LL cost(int, int), long long lo, long long hi) {
        base_cost = cost;
        n = N;

        while (lo < hi) {
            long long mid = lo + (hi-lo)/2;
            if (check(mid).second > k)  lo = mid+1;
            else                        hi = mid;
        }
        return check(lo).first - 1LL*k*lo;
    }
}

const int N = 1005;
long long a[N], W[N], WA[N];
long long ccost(int l,int r) {
    return (W[r] - W[l-1])*a[r] - (WA[r] - WA[l-1]);
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;

    while (cin>>n>>k) {
        for (int i=1; i<=n; i++)    {
            cin>>a[i]>>W[i];
            WA[i] = W[i] * a[i] + WA[i-1];
            W[i] += W[i-1];
        }
        cout<<ArrayPartitionDP::solve(n, k, ccost, 0, 1e12)<<endl;
    }
}
