/*
Source: Folklore, Anachor( get )
*/

#include<bits/stdc++.h>
using namespace std;

struct Fenwick {
    int N, K = 20;
    vector<long long> ft;
    Fenwick(int n) : N(n+1), ft(n+1) {}

    void add(int x, long long val) {
        for (int i=x; i<N; i+=i&-i) ft[i] += val;
    }

    long long sum(int x) {
        long long ans = 0;
        for (int i=x; i>0; i-=i&-i) ans += ft[i];
        return ans;
    }

    ///first k such that sum(k) >= x, if none returns N=n+1.
    int get(long long x) {
        int ans = 0;
        for (int i=K-1; i>=0; i--) {
            int nxt = ans + (1<<i);
            if (nxt < N && ft[nxt] < x) {
                ans = nxt;
                x -= ft[nxt];
            }
        }
        return ans+1;
    }
};

struct Fenwick {
    int N, K = 20;
    vector<int> ft;
    Fenwick(int n) : N(n+1), ft(n+1) {}

    void add(int x, int val) {
        for (int i=x; i<N; i+=i&-i) ft[i] += val;
    }

    int sum(int x) {
        int ans = 0;
        for (int i=x; i>0; i-=i&-i) ans += ft[i];
        return ans;
    }
};

/// Solves Timus 1521
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    Fenwick a, b;

    int n, k;
    cin>>n>>k;

    Fenwick ft(n);

    for (int i=1; i<=n; i++)    ft.add(i, 1);

    int last = 1;
    int ans = 0;
    for (int i=1; i<=n; i++) {
        int cur = (last+k-1)%(n-i+1);
        if (cur == 0)   cur = (n-i+1);

        int idx = ft.get(cur);
        cout<<idx<<" ";
        ft.add(idx, -1);
        last = cur;
    }
}
