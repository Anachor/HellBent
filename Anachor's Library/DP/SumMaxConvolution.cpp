///Author: Anachor

#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
namespace SumMaxConvolution {
    void solve(int l, int r, int optl, int optr, vector<LL> &a, vector<LL> &b, vector<LL> &c) {
        if (l > r)  return;
        int mid = (l+r)/2, opt = optl;
        LL ans = -1e18;

        for (int i=optl; i<=mid && i<=optr; i++) {
            if (mid-i < b.size() && a[i] + b[mid-i] > ans) {
                ans = a[i] + b[mid-i];
                opt = i;
            }
        }
        c[mid] = ans;
        solve(l, mid-1, optl, opt, a, b, c);
        solve(mid+1, r, opt, optr, a, b, c);
    }

    ///Input: a[0....n-1], b[0....m-1], where b is convex down (diff(b) is decreasing)
    ///returns c[0.....p-1],where c[k] = max(a[i] + b[k-i]). where p = min(n+m-1, kk);
    vector<LL> convolution(vector<LL> a, vector<LL> b, int kk) {
        int n = a.size(), m = b.size();
        int k = min(n+m-1, kk);
        vector<LL> c(k);
        solve(0, k-1, 0, n-1, a, b, c);

        return c;
    }
}

///Solves NAIPC 206: Jewel Thief (https://open.kattis.com/problems/thief)
const int K = 305;
vector<LL> costs[K];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    using namespace SumMaxConvolution;
    int n, k;
    cin>>n>>k;

    for (int i=1; i<=n; i++) {
        int x, y;
        cin>>x>>y;
        costs[x].push_back(y);
    }

    vector<LL> dp(k+1, -1e18);
    dp[0] = 0;

    for (int i=1; i<=k && i<K; i++) {
        if (costs[i].empty())   continue;

        sort(costs[i].rbegin(), costs[i].rend());
        costs[i].insert(costs[i].begin(), 0);
        for (int j=1; j<costs[i].size(); j++)   costs[i][j] += costs[i][j-1];
        vector<LL> newdp = dp;

        if (costs[i].size() > k/i)  costs[i].resize(k/i+1);

        for (int c=0; c<i; c++) {
            vector<LL> res;
            for (int j=c; j<dp.size(); j+=i)  res.push_back(dp[j]);
            res = convolution(res, costs[i], (k-c)/i+1);
            for (int j=0; j<res.size() && j*i+c <= k; j++)    newdp[j*i+c] = max(newdp[j*i+c], res[j]);
        }
        dp = newdp;
    }

    for (int i=1; i<=k; i++)    {
        dp[i] = max(dp[i-1], dp[i]);
        cout<<dp[i]<<" ";
    }
}
