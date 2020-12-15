///Solves SPOJ DYNACON2

#include<bits/stdc++.h>
using namespace std;

const int N = 1e5+7;

struct DSU {
    int rep[N], sz[N];
    vector<int> ops;
    int comps = 0;

    void init(int n) {
        for (int i=1; i<=n; i++)
            rep[i] = i, sz[i] = 1;
        ops.clear();
        comps = n;
    }

    int find(int u) {
        while(rep[u] != u)  u = rep[u];
        return u;
    }

    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v)   {
            ops.push_back(-1);
            return false;
        }
        if (sz[u] < sz[v])    swap(u, v);
        rep[v] = u;
        sz[u] += sz[v];
        ops.push_back(v);
        comps--;
        return true;
    }

    void rollback() {
        int u = ops.back();
        ops.pop_back();
        if (u == -1)    return;
        comps++;
        sz[rep[u]] -= sz[u];
        rep[u] = u;
    }
};

pair<int, int> qq[N];
vector<pair<int, int>> upd[4*N];
DSU dsu;

void add(int u, int st, int en, int l, int r, int x, int y) {
    if (l > en || st > r)   return;
    else if (l <= st && en <= r)        upd[u].push_back({x, y});
    else {
        int mid = (st+en)/2;
        add(2*u, st, mid, l, r, x, y);
        add(2*u+1, mid+1, en, l, r, x, y);
    }
}

void solve(int u, int st, int en) {
    for (auto pr: upd[u])   dsu.merge(pr.first, pr.second);
    if (st == en) {
        if (qq[st].first) {
            bool b = dsu.find(qq[st].first) == dsu.find(qq[st].second);
            cout<<(b ? "YES" : "NO")<<"\n";
        }
    }
    else {
        int mid = (st+en)/2;
        solve(2*u, st, mid);
        solve(2*u+1, mid+1, en);
    }
    for (auto pr: upd[u])   dsu.rollback();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin>>n>>q;

    if (q == 0) return 0;

    map<pair<int, int>, int> start;
    dsu.init(n);

    for (int i=1; i<=q; i++) {
        string s;
        int x, y;
        cin>>s>>x>>y;
        if (x > y)  swap(x, y);

        if (s == "add") {
            assert(start.count({x, y}) == 0);
            start[{x, y}] = i;
        }
        else if (s == "rem") {
            assert(start.count({x, y}) == 1);
            int l = start[{x, y}], r = i;
            start.erase({x, y});
            add(1,1,q,l,r,x,y);
        }
        else {
            qq[i] = {x, y};
        }
    }

    for (auto pr: start) {
        add(1, 1, q, pr.second, q, pr.first.first, pr.first.second);
    }

    solve(1, 1, q);
    return 0;
}
