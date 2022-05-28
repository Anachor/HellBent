/**
Solves dp[n][k] = min(dp[i-1][k-1] + cost(i, n)) using aliens trick
Req: cost() is QF. Complexity: O(n log^2)

Possible optimizations for O(n log n)
You can change solve1D() with linear CHT if cost(l, r) is of the form f(l)*g(r)
Alternatively, it may be possible to remove the binary search in 1D-1D.

Author: anachor
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL, LL>  PLL;

namespace ArrayPartitionDP {
    ///define this function in code
    LL base_cost(int l, int r);

    long long C;
    int n;

    PLL operator+ (const PLL &a, const PLL &b) {
        return PLL(a.first+b.first, a.second+b.second);
    }

    ///Solves dp[i] = min(dp[j] + cost(j+1, i)) given that cost() is QF
    ///returns {dp[n], min no of partitions}
    PLL solve1D() {
        auto cost = [&](int l, int r){ return PLL(base_cost(l, r)+C, 1); };
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

    PLL check(long long c) {
        C = c;
        return solve1D();
    }

    long long solve(int N, int k, long long lo, long long hi) {
        n = N;
        while (lo < hi) {
            long long mid = lo + (hi-lo)/2;
            if (check(mid).second > k)  lo = mid+1;
            else                        hi = mid;
        }
        return check(lo).first - 1LL*k*lo;
    }
}

///Solves https://tioj.ck.tp.edu.tw/problems/1986
const int N = 3e5+7;
long long a[N], A[N];

LL ArrayPartitionDP::base_cost(int l, int r) {
    int m = (l+r)/2;
    long long Z = (A[r] - A[m]) - (A[m] - A[l-1]) + (l%2 == r%2 ? a[m]: 0);
    return Z;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;

    while (cin>>n>>k) {
        for (int i=1; i<=n; i++)    cin>>a[i];
        sort(a+1, a+n+1);
        for (int i=1; i<=n; i++)    A[i] = A[i-1] + a[i];

        cout<<ArrayPartitionDP::solve(n, k, 0, 1e12)<<endl;
    }

}
