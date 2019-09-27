#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

#define NIL 0
#define MAX 100010
#define OPT(a, b) ((a)+(b))
#define jump(x) ((num[x] == 0) ? -1 : down[up[x]])

using namespace std;

/// Heavy Light Decomposition on Trees, 0 based indices
/// With RMQ support for nodes
/// Define the operation, default is +
/// x * NIL = x, NIL = 0 for addition/subtraction, 1 for multiplication, INF/-INF for min/max, etc
/// RMQ to add values on nodes, if required to set/replace values modify appropriately

namespace hld{
    int r, n, id;
    vector <int> adj[MAX];
    int nodeval[MAX], lazy[4 * MAX], tree[4 * MAX]; /// RMQ
    int parent[MAX], children[MAX], height[MAX], num[MAX], up[MAX], down[MAX]; /// HLD

    /// num[i] = 0 if the edge from i to parent[i] is not heavy, otherwise num[i] = unique id of the heavy edge
    /// down[i] = -1 if there is no heavy edge from i to it's children, otherwise down[i] = node number of the heavy child of i
    /// up[i] = i, if i is root, otherwise up[i] = node number of parent of i following only heavy up edges and one last light edge

    void dfs(int i, int p){
        parent[i] = p, children[i] = 1;
        if (i != p) height[i] = height[p] + 1;

        int j, x, len = adj[i].size();
        for (j = 0; j < len; j++){
            x = adj[i][j];
            if (x != p){
                dfs(x, i);
                children[i] += children[x];
            }
        }
    }

    /// build heavy light decomposition
    void build(int i, int p){ /// hash = 989687
        up[i] = i;
        if (num[i]) up[i] = up[p];

        int j, x, h = -1, l = adj[i].size();
        for (j = 0; j < l; j++){
            x = adj[i][j];
            if ((x != p) && ((children[x] << 1) >= children[i])) h = x;
        }

        if (h != -1){
            num[h] = ++id;
            build(h, i);
        }
        for (j = 0, down[i] = h; j < l; j++){
            x = adj[i][j];
            if ((x != p) && (x != h)) build(x, i);
        }
    }

    void update_rmq(int idx, int a, int b, int l, int r, int x); /// RMQ update defined for build
    void build(int root){ /// hash = 397248
        r = root, id = 0, height[r] = 0;
        dfs(r, r);
        build(r, r);
        for (int i = 0; i < n; i++){
            if (up[i] == i) up[i] = parent[i];
        }

        /// Builds RMQ
        clr(lazy);
        for (int i = 0; i < (MAX << 2); i++) tree[i] = NIL;
        for (int i = 0; i < n; i++){
            if (num[i]) update_rmq(1, 1, id, num[i], num[i], nodeval[i]);
        }
    }
    void build(){
        build(0); /// Root set to 0 by default!
    }

    int lca(int a, int b){
        while (up[a] != up[b]){
            if (height[up[a]] > height[up[b]]) a = up[a];
            else b = up[b];
        }

        if (a == b) return a;
        if (num[a] && num[b]){
            if (height[a] < height[b]) return a;
            else return b;
        }
        return up[a];
    }

    void add_edge(int a, int b){
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    void init(int nodes, int* ar){
        clr(num), n = nodes;
        for (int i = 0; i < MAX; i++) adj[i].clear();
        for (int i = 0; i < n; i++) nodeval[i] = ar[i];
    }

    /************** RMQ functions **************/


    /// Change lazy propagation accordingly
    /// Note lazy and updates set for adding values in node, update if set/replace operation
    inline void push(int idx, int a, int b){
        int c = (a + b) >> 1, d = c + 1, p = idx << 1, q = p | 1;
        if (lazy[idx]){
            tree[idx] += (lazy[idx] * (b - a + 1)); /// Change lazy according to operation
            if (a != b) lazy[p] += lazy[idx], lazy[q] += lazy[idx]; /// Change lazy according to operation
            lazy[idx] = 0;
        }
    }

    /// Change query accordingly
    int query_rmq(int idx, int a, int b, int l, int r){ /// hash = 87775
        int c = (a + b) >> 1, d = c + 1, p = idx << 1, q = p | 1;

        push(idx, a, b);
        if (a == l && b == r) return tree[idx];
        else if (r <= c) return query_rmq(p, a, c, l, r);
        else if (l >= d) return query_rmq(q, d, b, l, r);
        else return OPT(query_rmq(p, a, c, l, c), query_rmq(q, d, b, d, r));
    }

    /// Change update accordingly
    void update_rmq(int idx, int a, int b, int l, int r, int x){ /// hash = 487503
        int p = (idx << 1), q = p + 1, c = (a + b) >> 1, d = c + 1;

        if (a == l && b == r) lazy[idx] += x; /// Change lazy according to operation, change here if set
        push(idx, a, b);
        if (a == l && b == r) return;

        if (r <= c){
            push(q, d, b);
            update_rmq(p, a, c, l, r, x);
        }
        else if (l >= d){
            push(p, a, c);
            update_rmq(q, d, b, l, r, x);
        }
        else{
            update_rmq(p, a, c, l, c, x);
            update_rmq(q, d, b, d, r, x);
        }

        tree[idx] = OPT(tree[p], tree[q]);
    }

    /************** HLD + RMQ **************/

    /// Sum of all nodes in the path from u to l, l must be an ancestor of u
    int query_tree(int u, int l){ /// hash = 486879
        int res = NIL;
        while (height[u] > height[l]){
            if (num[u]){
                int v = jump(u);
                if (height[v] <= height[l]) v = down[l];
                res = OPT(res, query_rmq(1, 1, id, num[v], num[u]));
                u = parent[v];
            }
            else res = OPT(nodeval[u], res), u = parent[u];
        }
        return res;
    }

    /// Sum of all nodes in the path from u to v
    int query(int u, int v){
        int l = lca(u, v), res = NIL;
        res = OPT(res, query_tree(u, l));
        res = OPT(res, query_tree(v, l));
        if (!num[l]) res = OPT(nodeval[l], res);
        else res = OPT(query_rmq(1, 1, id, num[l], num[l]), res);
        return res;
    }

    /// Add w to all nodes in the path from u to l, l must be an ancestor of u
    void update_tree(int u, int l, int w){ /// hash = 423845
        while (height[u] > height[l]){
            if (num[u]){
                int v = jump(u);
                if (height[v] <= height[l]) v = down[l];
                update_rmq(1, 1, id, num[v], num[u], w);
                u = parent[v];
            }
            else nodeval[u] = OPT(nodeval[u], w), u = parent[u]; /// Change here if set instead of add
        }
    }

    /// Add w to all nodes in the path from u to v
    void update(int u, int v, int w){
        int l = lca(u, v);
        update_tree(u, l, w);
        update_tree(v, l, w);
        if (!num[l]) nodeval[l] = OPT(nodeval[l], w); /// Change here if set instead of add
        else update_rmq(1, 1, id, num[l], num[l], w);
    }
}

int n, q, ar[MAX];

int main(){
    int T = 0, t, i, j, k, l, x, u, v, w, res, flag;

    scanf("%d", &t);
    while (t--){
        clr(ar);
        scanf("%d", &n);
        hld::init(n, ar);

        for (i = 1; i < n; i++){
            scanf("%d %d", &u, &v);
            hld::add_edge(u, v);
        }
        hld::build();

        scanf("%d", &q);
        printf("Case #%d:\n", ++T);
        while (q--){
            scanf("%d %d %d", &u, &v, &w);
            hld::update(u, v, w);
        }
        for (i = 0; i < n; i++) printf("%d\n", hld::query(i, i));
    }
    return 0;
}
