#include <bits/stdtr1c++.h>

#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

/// Note: 0-based indexing for graphs

struct bridge{
    int u, v, w; /// Bridge from node u to v with cost w
    int f, s; /// Number of components in the first and second graph if bridge is disconnected

    bridge(){
    }

    bridge(int a, int b, int c, int d, int e){
        if (a > b) swap(a, b); /// Lower node first for convenience
        u = a, v = b, w = c, f = d, s = e;
    }
};

namespace br{
    typedef pair<int, int> Pair;

    bool visited[MAX];
    vector <bridge> B;
    vector <Pair> adj[MAX];
    tr1::unordered_set <long long> S;
    int n, r, dt, discover[MAX], low[MAX], cmp[MAX], num[MAX];

    void init(int nodes){
        n = nodes;
        for (int i = 0; i < MAX; i++) adj[i].clear();
    }

    void dfs(int i, int p){ /// hash = 60375
        visited[i] = true;
        discover[i] = low[i] = ++dt;
        int j, x, l, children = 0, len = adj[i].size();

        for (j = 0; j < len; j++){
            x = adj[i][j].first;
            if (!visited[x]){
                dfs(x, i);
                children++;
                low[i] = min(low[i], low[x]);

                if (low[x] > discover[i]){
                    if (!(j && adj[i][j - 1].first == x) || ( (j + 1) < len && adj[i][j + 1].first == x) ){ /// Handling multi-edge
                        l = dt - discover[x] + 1;
                        B.push_back( bridge(i, x, adj[i][j].second, l, cmp[i] - l) );
                    }
                }
            }
            else if (x != p) low[i] = min(low[i], discover[x]);
        }
    }

    void dfs(int i){
        low[dt++] = i;
        visited[i] = true;

        int j, x, len = adj[i].size();
        for (j = 0; j < len; j++){
            x = adj[i][j].first;
            if (!visited[x]){
                dfs(x);
            }
        }
    }

    /// Adds undirected edge from a to b with cost c or edge index number i
    void add(int a, int b, int c){
        adj[a].push_back(Pair(b, c));
        adj[b].push_back(Pair(a, c));
    }

    void FindBridge(){
        int i, j;
        B.clear();
        clr(visited);
        for (i = 0; i < n; i++) sort(adj[i].begin(), adj[i].end()); /// To handle multi-edges

        for (i = 0; i < n; i++){
            if (!visited[i]){
                dt = 0;
                dfs(i);
                for (j = 0; j < dt; j++) cmp[low[j]] = dt;
            }
        }

        clr(visited);
        for (i = 0; i < n; i++){
            if (!visited[i]){
                dt = 0;
                dfs(i, -1);
            }
        }
    }

    long long hashval(long long u, long long v){
        return (u * MAX) + v;
    }

    void dfsnum(int i){
        num[i] = r;
        visited[i] = true;

        int j, x, len = adj[i].size();
        for (j = 0; j < len; j++){
            x = adj[i][j].first;
            if (!visited[x] && !S.count(hashval(i, x))){
                dfsnum(x);
            }
        }
    }

    /// Call FindBridge before
    void BridgeTree(){
        S.clear();
        int i, j, x, u, v, len = B.size();

        for (i = 0; i < len; i++){
            S.insert(hashval(B[i].u, B[i].v));
            S.insert(hashval(B[i].v, B[i].u));
        }

        r = 0; /// Number of nodes in bridge tree
        clr(visited);
        for (i = 0; i < n; i++){
            if (!visited[i]){
                dfsnum(i);
                r++;
            }
        }

        for (i = 0; i < len; i++){
            u = B[i].u, v = B[i].v;
            /// Build the bridge tree here accordingly
        }
    }
}

int main(){
}
