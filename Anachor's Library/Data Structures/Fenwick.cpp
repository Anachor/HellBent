#include<bits/stdc++.h>
using namespace std;

const int N = 1.1e6+7, K = 21;
long long ft[N];

void add(int x, long long val) {
    for (int idx=x; idx<N; idx += idx&-idx)
        ft[idx] += val;
}

long long sum(int x) {
    long long ans = 0;
    for (int idx=x; idx>0; idx-=idx&-idx)
        ans += ft[idx];
    return ans;
}

///first k such that sum(k) >= x, if none returns N.
int get(long long x) {
    int ans = 0;
    for (int i=K-1; i>=0; i--) {
        int nxt = ans + (1<<i);
        if (nxt < N && ft[nxt] < x) {
            ans += 1<<i;
            x-=ft[nxt];
        }
    }
    return ans+1;
}

/// Solves Timus 1896
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin>>n>>k;

    for (int i=1; i<=n; i++)    add(i, 1);

    int last = 1;
    int ans = 0;
    for (int i=1; i<=n; i++) {
        int cur = (last+k-1)%(n-i+1);
        if (cur == 0)   cur = (n-i+1);

        int idx = get(cur);
        ans ^= abs(idx-i);
        add(idx, -1);
        last = cur;
    }

    cout<<ans<<endl;
}
