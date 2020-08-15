///Solves CF 600E - Lomsat gelral

#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int N = 1e5+7;
vector<int> adj[N];
int cnt[N], col[N];
int mx[N], sz[N];
int st[N], en[N], id[2*N];
LL ans[N];

void setup(int u, int par, int &time)
{
    sz[u] = 1;
    st[u] = ++time;
    id[time] = u;
    for (auto v: adj[u])
        if (v!=par)
            setup(v, u, time),
            sz[u] += sz[v];

    en[u] = ++time;
}

void dfs(int u, int par, int keep)
{
    int big=-1, maxx = 0;
    for (auto v: adj[u])
        if (v!=par && sz[v] > maxx)
            maxx = sz[v], big = v;

    for (auto v: adj[u])
        if (v!=par && v!=big)
            dfs(v, u, 0);

    if (big!=-1) dfs(big, u, 1);
    if (big!=-1)  mx[u] = mx[big], ans[u] = ans[big];
    cnt[col[u]]++;


    if (cnt[col[u]] > mx[u])   mx[u] = cnt[col[u]], ans[u] = col[u];
    else if (cnt[col[u]] == mx[u])  ans[u] += col[u];

    for (auto v: adj[u])
        if (v!=par && v!= big)
            for (int i = st[v]; i<en[v]; i++) {
                cnt[col[id[i]]]++;
                if (cnt[col[id[i]]] > mx[u])   mx[u] = cnt[col[id[i]]], ans[u] = col[id[i]];
                else if (cnt[col[id[i]]] == mx[u])  ans[u] += col[id[i]];
            }

    if (keep == 0)
        for (int i=st[u]; i<en[u]; i++)
            cnt[col[id[i]]]--;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin>>n;

    for (int i=1; i<=n; i++)
        cin>>col[i];

    for (int i=1; i<n; i++)
    {
        int x, y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    int time = 0;
    setup(1, -1, time);
    dfs(1, -1, 0);

    for (int i=1; i<=n; i++)
        cout<<ans[i]<<" ";
}
