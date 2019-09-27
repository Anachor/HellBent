#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 4;
const int LOG = 30;

int a[N], n;
int par[N];
int totComp;
long long MST = 0;

vector<int> comp[N];
vector<int> mst[N];

void addEdge(int u,int v) {
    mst[u].push_back(v);
    mst[v].push_back(u);
    --totComp;
    MST = MST + (long long) (a[u] ^ a[v]);
}

int to[N*LOG + 100][2];
int cnt[N*LOG + 100];
int totNodes = 1;

void add(int x, int idx) {
    int cur = 1;
    for(int k = 30 ; k >= 0 ; k--) {
        cnt[cur]++;
        int b = ((x>>k)&1);
        if (!to[cur][b]) to[cur][b] = ++totNodes;
        cur = to[cur][b];
    }
    cnt[cur]++;
    to[cur][0] = idx;
}

void Erase(int x) {
    int cur = 1;
    for(int k = 30 ; k >= 0 ; k--) {
        cnt[cur]--;
        int b = ((x>>k)&1);
        if (!to[cur][b]) assert(1 == 0), to[cur][b] = ++totNodes;
        cur = to[cur][b];
    }
    cnt[cur]--;
}

int query(int x) {
    int cur = 1;
    for(int k = 30 ; k >= 0 ; k--) {
        int b = ((x>>k)&1);
        if (to[cur][b] && cnt[to[cur][b]]) {
            cur = to[cur][b];
        } else {
            cur = to[cur][b^1];
        }
    }
    return to[cur][0];
}

int parent(int u) {
    if (par[u] == u) return u;
    return par[u] = parent(par[u]);
}

int main() {
    scanf("%d",&n);
    map <int,int> ocr;
    totComp = n;
    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
        if (ocr.find(a[i]) == ocr.end()) {
            ocr[a[i]] = i;
            comp[i].push_back(i);
            par[i] = i;
            add(a[i],i);
        }
        else {
            int u = ocr[a[i]];
            par[i] = u;
            addEdge(i,u);
        }
    }

    while(totComp > 1) {
        set < pair<int,int> > edge;
        for(int i = 1; i <= n; i++) {
            if (comp[i].size() == 0) continue;
            for(int u : comp[i]) {
                Erase(a[u]);
            }
            int xorMin = 2e9, U, V;
            for(int u : comp[i]) {
                int v = query(a[u]);
                int xorCur = a[u] ^ a[v];
                if (xorCur < xorMin) {
                    xorMin = xorCur;
                    U = u, V = v;
                }
            }
            if(U > V) swap(U,V);
            edge.insert({U,V});
            for(int u : comp[i]) {
                add(a[u],u);
            }
        }

        for(pair<int,int> curEdge : edge) {
            int u = curEdge.first , v = curEdge.second;
            int pu = parent(u) , pv = parent(v);
            if(pu == pv) continue ;
            addEdge(u,v);
            if (comp[pu].size() < comp[pv].size()) swap(pu,pv);
            for(int node : comp[pv]) {
                par[node] = pu;
                comp[pu].push_back(node);
            }
            comp[pv].clear();
        }
    }

    cout << MST << endl;
}
