///Implementation of https://codeforces.com/blog/entry/83467
/// Author: anachor
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5+7;

struct DSU {
    int rep[N], sz[N];
    vector<int> ops;

    void init() {
        for (int i=0; i<N; i++)
            rep[i] = i, sz[i] = 1;
        ops.clear();
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
        return true;
    }

    void rollback() {
        int u = ops.back();
        ops.pop_back();
        if (u == -1)    return;
        sz[rep[u]] -= sz[u];
        rep[u] = u;
    }
};


struct Update {
    int type, u, v;
};

struct QueueUndoTrick {
    vector<Update> updates;
    int cnt0 = 0;
    DSU dsu;

    QueueUndoTrick() {
        dsu.init();
    }

    void pushUpdate(const Update &up) {
        dsu.merge(up.u, up.v);
        updates.push_back(up);
        if (up.type == 0)   cnt0++;
    }

    void popUpdate() {
        if (updates.back().type == 0)   cnt0--;
        updates.pop_back();
        dsu.rollback();
    }

    void update(int u, int v) {
        pushUpdate({1, u, v});
    }

    int query(int x) {
        return dsu.sz[dsu.find(x)];
    }

    void undoFront() {
        if (cnt0 == 0) {
            vector<Update> temp;
            for (Update &up: updates)        temp.push_back(up), popUpdate();
            reverse(temp.begin(), temp.end());
            for (Update &up: temp)           up.type = 0, pushUpdate(up);
        }

        if (updates.back().type == 1) {
            vector<Update> temp[2];
            do {
                temp[updates.back().type].push_back(updates.back());
                popUpdate();
            } while (cnt0 > 0 && temp[0].size() != temp[1].size());

            reverse(temp[0].begin(), temp[0].end());
            reverse(temp[1].begin(), temp[1].end());
            for (Update up: temp[1])     pushUpdate(up);
            for (Update up: temp[0])     pushUpdate(up);
        }

        assert(updates.back().type == 0);
        popUpdate();
    }
};

///Solves CF 1423 H
int cnt[N];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q, k;
    cin>>n>>q>>k;

    QueueUndoTrick solver;

    int d = 0;
    while (q--) {

        int t;
        cin>>t;

        if (t == 1) {
            int x, y;
            cin>>x>>y;
            solver.update(x, y);
            cnt[d]++;
        }
        else if (t==2) {
            int x;
            cin>>x;
            cout<<solver.query(x)<<"\n";
        }
        else {
            d++;
            if (d >= k) {
                for (int i=0; i<cnt[d-k]; i++)  solver.undoFront();
            }
        }
    }
}
