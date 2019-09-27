#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

struct Edge{
    int u, v, w;

    Edge(){}
    Edge(int a, int b, int c){
        u = a, v = b, w = c;
    }
};

/// Directed minimum spanning tree in O(n * m)
/// Constructs a rooted tree of minimum total weight from the root node
/// Returns -1 if no solution from root

int directed_MST(int n, vector <Edge> E, int root){ /// hash = 547539
    const int INF = (1 << 30) - 30;

    int i, j, k, l, x, y, res = 0;
    vector <int> cost(n), parent(n), label(n), comp(n);

    for (; ;){
        for (i = 0; i < n; i++) cost[i] = INF;
        for (auto e: E){
            if (e.u != e.v && cost[e.v] > e.w){
                cost[e.v] = e.w;
                parent[e.v] = e.u;
            }
        }

        cost[root] = 0;
        for (i = 0; i < n && cost[i] != INF; i++){};
        if (i != n) return -1; /// No solution

        for (i = 0, k = 0; i < n; i++) res += cost[i];
        for (i = 0; i < n; i++) label[i] = comp[i] = -1;

        for (i = 0; i < n; i++){
            for (x = i; x != root && comp[x] == -1; x = parent[x]) comp[x] = i;
            if (x != root && comp[x] == i){
                for (k++; label[x] == -1; x = parent[x]) label[x] = k - 1;
            }
        }

        if (k == 0) break;
        for (i = 0; i < n; i++){
            if (label[i] == -1) label[i] = k++;
        }

        for (auto &e: E){
            x = label[e.u], y = label[e.v];
            if (x != y) e.w -= cost[e.v];
            e.u = x, e.v = y;
        }
        root = label[root], n = k;
    }
    return res;
}

int main(){
    int T = 0, t, n, m, i, j, k, u, v, w, res;

    scanf("%d", &t);
    while (t--){
        vector <Edge> E;
        scanf("%d %d", &n, &m);
        for (i = 0; i < m; i++){
            scanf("%d %d %d", &u, &v, &w);
            E.push_back(Edge(u, v, w));
        }

        res = directed_MST(n, E, 0);
        if (res == -1) printf("Case #%d: Possums!\n", ++T);
        else printf("Case #%d: %d\n", ++T, res);
    }
    return 0;
}
