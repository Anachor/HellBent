#include<bits/stdc++.h>
using namespace std;

const int N = 1e6+7;
int n; // number of nodes
vector<int> adj[N]; // adjacency list of graph
bool visited[N];
int tin[N], fup[N];
int isAP[N];
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = fup[v] = timer++;
    int children=0;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            fup[v] = min(fup[v], tin[to]);
        } else {
            dfs(to, v);
            fup[v] = min(fup[v], fup[to]);
            if (fup[to] >= tin[v] && p!=-1)
                isAP[v] = 1;
            ++children;
        }
    }
    if(p == -1 && children > 1)
        isAP[v] = 1;
}

void find_cutpoints() {
    timer = 0;

    memset(visited, 0, sizeof visited);
    memset(tin, -1, sizeof tin);
    memset(fup, -1, sizeof fup);
    memset(isAP, 0, sizeof isAP);

    for (int i = 1; i <= n; ++i) {
        if (!visited[i])
            dfs(i);
    }
}

int main()
{
    int m;
    while (true)
    {
        cin>>n>>m;
        if (!n && !m)   break;

        for (int i=1; i<=n; i++)
            adj[i].clear();

        while (m--)
        {
            int x, y;
            cin>>x>>y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        find_cutpoints();

        int ans = 0;
        for (int i=1; i<=n; i++)
            if (isAP[i])
                ans++;
        cout<<ans<<endl;
    }
}
