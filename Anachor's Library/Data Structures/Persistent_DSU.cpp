///Author: anachor

#include<bits/stdc++.h>
using namespace std;

const int N = 2e5+7;
struct PersistentDSU {
    vector<pair<int, int>> rep[N], sz[N];
    void init() {
        for (int i=0; i<N; i++) {
            rep[i].push_back({0, i});
            sz[i].push_back({0, 1});
        }
    }

    pair<int, int> find(int u, int ver) {
        while(true) {
            pair<int, int> pr = {ver, N};
            int par = (--upper_bound(rep[u].begin(), rep[u].end(), pr))->second;
            if (par != u)   u = par;
            else {
                int siz = (--upper_bound(sz[u].begin(), sz[u].end(), pr))->second;
                return {u, siz};
            }
        }
    }

    bool merge(int u, int v, int ver, int curid) {
        int szu, szv;
        tie(u, szu) = find(u, ver);
        tie(v, szv) = find(v, ver);

        if (u == v)   return false;
        if (szu < szv)    swap(u, v), swap(szu, szv);
        rep[v].push_back({curid, u});
        sz[u].push_back({curid, szu + szv});
        return true;
    }
} dsu;

///Solves https://old.yosupo.jp/problem/persistent_unionfind
int main() {
    int n, q;
    cin>>n>>q;

    dsu.init();

    for (int i=1; i<=q; i++) {
        int t, k, u, v;
        cin>>t>>k>>u>>v;
        k++;

        if (t==0)   dsu.merge(u, v, k, i);
        else        cout<< (dsu.find(u, k).first == dsu.find(v, k).first)<<"\n";
    }
}
