#include <bits/stdtr1c++.h>

#define MAXN 5010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// Dinic's algorithm for directed graphs (0 based index for graphs)
/// For undirected graphs, just add two directed edges

const long long INF = (~0ULL) >> 1;

namespace flow{
    int n, s, t, ptr[MAXN], dis[MAXN], Q[MAXN];
    long long cap[MAXN][MAXN], flow[MAXN][MAXN];

    inline void init(int nodes, int source, int sink){
        clr(cap), clr(flow);
        n = nodes, s = source, t = sink;
    }

    inline void addEdge(int a, int b, int c){
        cap[a][b] += c;
    }

    inline bool bfs(){
        int i, j, f = 0, l = 0;
        memset(dis, -1, sizeof(dis[0]) * n);

        dis[s] = 0, Q[l++] = s;
        while (f < l){
            i = Q[f++];
            for (j = 0; j < n; j++){
                if (dis[j] == -1 && flow[i][j] < cap[i][j]){
                    Q[l++] = j;
                    dis[j] = dis[i] + 1;
                }
            }
        }
        return (dis[t] != -1);
    }

    long long dfs(int i, long long f){
        if (i == t || !f) return f;
        for (int &j = ptr[i]; j < n; j++){
            if (dis[j] == (dis[i] + 1)){
                long long x = dfs(j, min(f, cap[i][j] - flow[i][j]));
                if (x){
                    flow[i][j] += x, flow[j][i] -= x;
                    return x;
                }
            }
        }
        return 0;
    }

    long long dinic(){
        long long res = 0;
        while (bfs()){
            memset(ptr, 0, n * sizeof(ptr[0]));
            while (long long f = dfs(s, INF)){
                res += f;
            }
        }
        return res;
    }
}

int main(){
    int n, i, j, k, a, b, c, s, t, m;

    n = MAXN - 10;
    s = 0, t = n - 1;
    flow::init(n, s, t);

    m = n * 1.75;
    while (m--){
        a = ran(0, n - 1);
        b = ran(0, n - 1);
        c = ran(1, 1000000000);
        flow::addEdge(a, b, c);
    }

    clock_t start = clock();
    printf("%lld\n", flow::dinic());
    fprintf(stderr, "%0.6f\n", (clock() - start) / (1.0 * CLOCKS_PER_SEC));
    return 0;
}
