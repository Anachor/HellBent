#include <stdio.h>
#include <bits/stdtr1c++.h>

#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// 2 SAT (1 based index for variables)
/// Each variable can have two possible values (true or false)
/// Variables must satisfy a system of constraints on pairs of variables

namespace sat{
    bool visited[MAX * 2];
    vector <int> adj[MAX * 2], rev[MAX * 2];
    int n, m, l, dfs_t[MAX * 2], order[MAX * 2], parent[MAX * 2];

    inline int neg(int x){
        return ((x) <= n ? (x + n) : (x - n));
    }

    /// Call init once
    void init(int nodes){
        n = nodes, m = nodes * 2;
        for (int i = 0; i < MAX * 2; i++){
            adj[i].clear();
            rev[i].clear();
        }
    }

    /// Add implication, if a then b
    inline void add_implication(int a, int b){
        if (a < 0) a = n - a;
        if (b < 0) b = n - b;

        adj[a].push_back(b);
        rev[b].push_back(a);
    }

    inline void add_or(int a, int b){
        add_implication(-a, b);
        add_implication(-b, a);
    }

    inline void add_xor(int a, int b){
        add_or(a, b);
        add_or(-a, -b);
    }

    inline void add_and(int a, int b){
        add_or(a, b);
        add_or(a, -b);
        add_or(-a, b);
    }

    /// force variable x to be true (if x is negative, force !x to be true)
    inline void force_true(int x){
        if (x < 0) x = n - x;
        add_implication(neg(x), x);
    }

    /// force variable x to be false (if x is negative, force !x to be false)
    inline void force_false(int x){
        if (x < 0) x = n - x;
        add_implication(x, neg(x));
    }

    inline void topsort(int i){
        visited[i] = true;
        int j, x, len = rev[i].size();

        for (j = 0; j < len; j++){
            x = rev[i][j];
            if (!visited[x]) topsort(x);
        }
        dfs_t[i] = ++l;
    }

    inline void dfs(int i, int p){
        parent[i] = p;
        visited[i] = true;
        int j, x, len = adj[i].size();

        for (j = 0; j < len; j++){
            x = adj[i][j];
            if (!visited[x]) dfs(x, p);
        }
    }

    void build(){
        int i, x;
        clr(visited);
        for (i = m, l = 0; i >= 1; i--){
            if (!visited[i]){
                topsort(i);
            }
            order[dfs_t[i]] = i;
        }

        clr(visited);
        for (i = m; i >= 1; i--){
            x = order[i];
            if (!visited[x]){
                dfs(x, x);
            }
        }
    }

    /// Returns true if the system is 2-satisfiable and returns the solution (nodes set to true) in vector res
    bool satisfy(vector <int>& res){
        build();
        clr(visited);

        for (int i = 1; i <= m; i++){
            int x = order[i];
            if (parent[x] == parent[neg(x)]) return false;

            if (!visited[parent[x]]){
                visited[parent[x]] = true;
                visited[parent[neg(x)]] = false;
            }
        }

        res.clear();
        for (int i = 1; i <= n; i++){
            if (visited[parent[i]]) res.push_back(i);
        }
        return true;
    }
}

int main(){
    return 0;
}
