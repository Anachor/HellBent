#include <bits/stdtr1c++.h>

#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// Hopcroft karp in O(m * sqrt(n))
namespace hc{ /// hash = 393558
    bool visited[MAX];
    vector <int> adj[MAX];
    int n, L[MAX], R[MAX], Q[MAX], len[MAX], dis[MAX], parent[MAX];

    inline void init(int nodes){ /// Number of vertices in the left set, or max(left_set, right_set)
        n = nodes, clr(len);
        for (int i = 0; i < MAX; i++) adj[i].clear();
    }

    inline void add_edge(int u, int v){ /// 0 based index
        len[u]++;
        adj[u].push_back(v);
    }

    bool dfs(int i){
        for (int j = 0; j < len[i]; j++){
            int x = adj[i][j];
            if (L[x] == -1 || (parent[L[x]] == i)){
                if (L[x] == -1 || dfs(L[x])){
                    L[x] = i, R[i] = x;
                    return true;
                }
            }
        }
        return false;
    }

    bool bfs(){
        clr(visited);
        int i, j, x, d, f = 0, l = 0;

        for (i = 0; i < n; i++){
            if (R[i] == -1){
                visited[i] = true;
                Q[l++] = i, dis[i] = 0;
            }
        }

        while (f < l){
            i = Q[f++];
            for (j = 0; j < len[i]; j++){
                x = adj[i][j], d = L[x];
                if (d == -1) return true;

                else if (!visited[d]){
                    Q[l++] = d;
                    parent[d] = i, visited[d] = true, dis[d] = dis[i] + 1;
                }
            }
        }
        return false;
    }

    int hopcroft_karp(){
        int res = 0;
        memset(L, -1, sizeof(L));
        memset(R, -1, sizeof(R));

        while (bfs()){
            for (int i = 0; i < n; i++){
                if (R[i] == -1 && dfs(i)) res++;
            }
        }
        return res;
    }
}

int main(){
    int n, m, r, i, j, a, b;

    scanf("%d %d %d", &n, &m, &r);
    hc::init(max(n, m));
    while (r--){
        scanf("%d %d", &a, &b);
        hc::add_edge(--a, --b);
    }

    printf("%d\n", hc::hopcroft_karp());
    return 0;
}
