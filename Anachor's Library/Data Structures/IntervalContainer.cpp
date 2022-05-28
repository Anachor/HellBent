///Author: anachor

#include<bits/stdc++.h>
using namespace std;

/// Maintains an array of size n, initially all values are same.
/// Color(l, r, c): Set a[i] = c for l <= i <= r.
/// get(x): return a[x];
struct IntervalContainer {
    int n;
    map<int, int> a;

    int get(int x) {
        auto it = a.upper_bound(x);
        return (--it)->second;
    }

    /// Container size n with initial value c
    IntervalContainer(int n, int c) {
        this->n = n;
        a[1] = c;
        a[n+1] = c;
    }

    void color(int l, int r, int c) {
        int rc = get(r);
        a[l] = c;
        auto it = a.upper_bound(l);
        while (it->first <= r) it = a.erase(it);
        if (it->first > r+1)   a[r+1] = rc;
    }
};



///Solves CF 1208E
const int N = 1e6+7;
typedef long long LL;
typedef pair<int, int> PII;
LL ans[N];

int main() {
    int n, w;
    cin>>n>>w;

    for (int i=1; i<=n; i++) {
        int m;
        cin>>m;

        vector<PII> row(m);
        for (int j=0; j<m; j++) {
            cin>>row[j].first;
            row[j].second = j+1;
        }

        sort(row.begin(), row.end());
        IntervalContainer ic(w, -1e9-7);

        bool nopos = true;

        for (PII pr: row) {
            int v = pr.first;
            int pos = pr.second;
            if (v > 0 && nopos) {
                nopos = false;
                if (m<w) ic.color(1, w-m, 0);
                if (m<w) ic.color(m+1, w, 0);
            }
            int mn = pos, mx = w-m+pos;
            ic.color(mn, mx, v);
        }

        if (nopos) {
            nopos = false;
            if (m<w) ic.color(1, w-m, 0);
            if (m<w) ic.color(m+1, w, 0);
        }

        vector<PII> v;
        for (auto pr: ic.a) v.push_back(pr);

        for (int i=1; i<v.size(); i++) {
            int l = v[i-1].first;
            int r = v[i].first;
            int c = v[i-1].second;
            ans[l] += c;
            ans[r] -= c;
//            cout<<l<<" "<<r<<" "<<c<<endl;
        }
    }

    for (int i=1; i<=w; i++) {
        ans[i] += ans[i-1];
        cout<<ans[i]<<" ";
    }

}

