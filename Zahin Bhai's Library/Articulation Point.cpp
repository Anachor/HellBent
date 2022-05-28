#include <bits/stdtr1c++.h>

#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

/// Note: 0-based indexing for graphs
namespace ap{
    vector <int> adj[MAX];
    bool visited[MAX], cut[MAX];
    int n, disc_t, discover[MAX], low[MAX];

    void init(int nodes){
        n = nodes;
        for (int i = 0; i < MAX; i++) adj[i].clear();
    }

    void dfs(int i, int p){
        visited[i] = true;
        discover[i] = low[i] = ++disc_t;
        int j, x, children = 0, len = adj[i].size();

        for (j = 0; j < len; j++){
            x = adj[i][j];
            if (!visited[x]){
                children++;
                dfs(x, i);
                low[i] = min(low[i], low[x]);

                if ((low[x] >= discover[i])){
                    if (!(p == -1 && children < 2)){
                        cut[i] = true;
                    }
                }
            }
            else if (x != p) low[i] = min(low[i], discover[x]);
        }
    }

    /// Adds undirected edge from a to b with cost or edge index number i
    /// Note that i is optional, it's not needed to find bridges

    void add(int a, int b){
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    void articulate(){
        int i, j;
        clr(visited), clr(cut);

        for (i = 0; i < n; i++){
            if (!visited[i]){
                disc_t = 0;
                dfs(i, -1);
            }
        }
        /// cut[i] = true if i is an articulation point, false otherwise
    }
}

int main(){
}
