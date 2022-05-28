/**
Linear Convex Hull Trick
Requirement:
    Minimum:
        M increasing, x decreasing, useless(s-1, s-2, s-3)
        M decreasing, x increasing, useless(s-3, s-2, s-1)
    Maximum:
        M increasing, x increasing, useless(s-3, s-2, s-1)
        M decreasing, x decreasing, useless(s-1, s-2, s-3)

If queries are in arbitrary order, use query2 O(logn) per query.

Source: Rezwan, Anachor (query2)
**/


#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

struct CHT {
    vector<LL> M;
    vector<LL> C;
    int ptr = 0;

    ///Use double comp if M,C is LL range
    bool useless(int l1, int l2, int l3) {
        return (C[l3]-C[l1])*(M[l1]-M[l2]) <= (C[l2]-C[l1])*(M[l1]-M[l3]);
    }

    LL f(int id, LL x) {
        return M[id]*x+C[id];
    }

    void add(LL m, LL c) {
        M.push_back(m);
        C.push_back(c);
        int s = M.size();

        while (s >= 3 && useless(s-3, s-2, s-1)) {
            M.erase(M.end()-2);
            C.erase(C.end()-2);
            s--;
        }
    }

    LL query(LL x) {
        if (ptr >= M.size()) ptr = M.size()-1;
        while (ptr < M.size()-1 && f(ptr, x) > f(ptr+1, x)) ptr++; /// change > to < for maximum
        return f(ptr, x);
    }
    
    LL query2(LL x) {
        int lo=0, hi=M.size()-1;
        while(lo<hi) {
            int mid = (lo+hi)/2;
            if (f(mid, x) > f(mid+1, x))    lo = mid+1; /// change > to < for maximum
            else                            hi = mid;
        }
        return f(lo, x);
    }
};


///Solves SPOJ Acquire
const int N = 1e5+7;
LL dp[N];

typedef pair<LL, LL> PLL;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;

    vector<PLL> v(n), t;

    for (int i=0; i<n; i++) cin>>v[i].first>>v[i].second;
    sort(v.begin(), v.end());

    for (int i=0; i<n; i++) {
        while (t.size() && t.back().second <= v[i].second)  t.pop_back();
        t.push_back(v[i]);
    }

    n = t.size();
    dp[0] = 0;

    CHT cht;
    for (int i=1; i<=n; i++) {
        cht.add(t[i-1].second, dp[i-1]);
        dp[i] = cht.query(t[i-1].first);
    }

    cout<<dp[n]<<endl;
}


