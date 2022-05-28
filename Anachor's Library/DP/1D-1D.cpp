///Author: anachor

#include<bits/stdc++.h>
using namespace std;

///Solves dp[i] = min(dp[j] + cost(j+1, i)) given that cost() is QF
long long solve1D(int n, long long cost(int, int)) {
    vector<long long> dp(n+1), opt(n+1);
    deque<pair<int, int>> dq;
    dq.push_back({0, 1});
    dp[0] = 0;

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

///Solves https://open.kattis.com/problems/coveredwalkway
const int N = 1e6+7;
long long x[N];
int c;
long long cost(int l, int r) {
    return (x[r] - x[l])*(x[r] - x[l]) + c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n>>c;
    for (int i=1; i<=n; i++)    cin>>x[i];
    cout<<solve1D(n, cost)<<endl;
}
