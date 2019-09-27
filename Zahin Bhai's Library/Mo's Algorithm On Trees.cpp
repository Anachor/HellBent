#include <bits/stdtr1c++.h>

#define LOG 18
#define MAX 100010
#define MAXQ 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// SPOJ Count On A Tree II, Number of distinct values on nodes on the path from U to V

namespace mo{ /// Mo's Algorithm on Trees, 0-based index
    int q, counter, block_size = 337, out[MAXQ], freq[MAX]; /// block_size = sqrt(2*N)

    struct Query{
        int l, r, s, d, idx;

        inline Query() {}
        inline Query(int a, int b, int p, int c){
            idx = c;
            l = a, r = b, s = p, d = l / block_size;
        }

        inline bool operator < (const Query& other) const{
            if (d != other.d) return (d < other.d);
            return ((d & 1) ? (r < other.r) : (r > other.r));
        }
    } Q[MAXQ];

    vector <int> adj[MAX];
    int n, r, t, S[MAX], E[MAX], ar[MAX << 1], parent[MAX], depth[MAX], lg[MAX], nodeval[MAX], nodecount[MAX], dp[MAX][LOG];

    void init(int nodes, int root, int sz, int* nodevalT){ /// Values on nodes, modify appropriately if values on edges
        lg[0] = lg[1] = 0;
        block_size = max(1, sz);
        clr(freq), clr(nodecount);
        q = 0, t = 0, n = nodes, r = root;
        for (int i = 0; i <= n; i++) adj[i].clear();
        for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
        for (int i = 0; i < n; i++) nodeval[i] = nodevalT[i];
    }

    inline void add_edge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    inline int lca(int a, int b){
        if (a == b) return a;
        if (depth[a] < depth[b]) swap(a, b);

        for (int i = lg[depth[a] - depth[b]]; i >= 0; i--){
            if ((depth[a] - (1 << i)) >= depth[b]) a = dp[a][i];
        }
        if (a == b) return a;

        for (int i = lg[depth[a]]; i >= 0; i--){
            if (dp[a][i] != dp[b][i]){
                a = dp[a][i];
                b = dp[b][i];
            }
        }

        return (a == b) ? a : parent[a];
    }

    inline void dfs(int i, int p){
        S[i] = t, ar[t++] = i;
        int j, len = adj[i].size();
        for (j = 0, parent[i] = p; j < len; j++){
            if (adj[i][j] != p){
                depth[adj[i][j]] = depth[i] + 1;
                dfs(adj[i][j], i);
            }
        }
        E[i] = t, ar[t++] = i;
    }

    inline void build(){
        depth[r] = 0;
        dfs(r, r);

        for (int l = 0; l <= lg[n]; l++){
            for (int i = 0; i < n; i++){
                if (!l) dp[i][l] = parent[i];
                else dp[i][l] = dp[dp[i][l - 1]][l - 1];
            }
        }
    }

    inline void push(int a, int b, int idx){
        if (depth[a] > depth[b]) swap(a, b);
        int l = lca(a, b);
        if (a == l) Q[q++] = Query(S[a], S[b], -1, idx);
        else{
            if (E[b] <= S[a]) Q[q++] = Query(E[b], S[a], S[l], idx);
            else Q[q++] = Query(E[a], S[b], S[l], idx);
        }
    }

    /// If a node occurs twice in a range, then both its value needs to be ignored
    inline void insert(int idx){
        int x = ar[idx];
        if (nodecount[x]){
            freq[nodeval[x]]--;
            if (freq[nodeval[x]] == 0) counter--;
        }
        else{
            if (freq[nodeval[x]] == 0) counter++;
            freq[nodeval[x]]++;
        }
        nodecount[x] ^= 1;
    }

    inline void erase(int idx){
        int x = ar[idx];
        if (!nodecount[x]){
            if (freq[nodeval[x]] == 0) counter++;
            freq[nodeval[x]]++;
        }
        else{
            freq[nodeval[x]]--;
            if (freq[nodeval[x]] == 0) counter--;
        }
        nodecount[x] ^= 1;
    }

    inline void run(){
        counter = 0;
        sort(Q, Q + q);
        int i, l, r, a = 0, b = 0; /// Change here if 1-based array

        for (i = 0; i < q; i++){
            l = Q[i].l, r = Q[i].r;
            while (a > l) insert(--a);
            while (b <= r) insert(b++);
            while (a < l) erase(a++);
            while (b > (r + 1)) erase(--b);
            if (Q[i].s != -1) insert(Q[i].s);
            out[Q[i].idx] = counter;
            if (Q[i].s != -1) erase(Q[i].s);
        }
    }

    inline void print(){
        for (int i = 0; i < q; i++) printf("%d\n", out[i]);
    }
}

int T[MAX], H[MAX];
tr1::unordered_map <int, int> mp;

int main(){
    int n, q, h, i, j, k, a, b;

    scanf("%d %d", &n, &q);
    for (i = 0; i < n; i++) scanf("%d", &T[i]);

    /// Co-ordinate compression, necessary only for this problem
    /*** mp.clear();
    for (h = 0, i = 0; i < n; i++) H[i] = T[i];
    sort(H, H + n);
    H[n] = -1;
    for (i = 0; i < n; i++){
        if (H[i] != H[i + 1]) mp[H[i]] = ++h;
    }
    for (i = 0; i < n; i++) T[i] = mp[T[i]]; ***/

    mo::init(n, 0, 337, T);
    for (i = 1; i < n; i++){
        scanf("%d %d", &a, &b);
        a--, b--;
        mo::add_edge(a, b);
    }
    mo::build();

    for (i = 0; i < q; i++) {
        scanf("%d %d", &a, &b);
        a--, b--;
        mo::push(a, b, i);
    }

    mo::run();
    mo::print();
    return 0;
}
