#include <bits/stdtr1c++.h>

#define MAX 1010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

/// 2D Fenwick tree, Point updates and range queries
class Fenwick2D{
    public:
    int n, m, tree[MAX][MAX];

    Fenwick2D(){
    }

    Fenwick2D(int a, int b){
        clr(tree);
        n = a, m = b;
    }

    /// Add v to ar[i][j]
    void update(int i, int j, int v){
        while (i <= n){
            int k = j;
            while (k <= m){
                tree[i][k] += v;
                k += (k & (-k));
            }
            i += (i & (-i));
        }
    }

    /// Query for sum of the sub-rectangle from upper-left [i,j] to lower-right [n,n]
    int query(int i, int j){
        if ((i < 0) || (j < 0) || (i > n) || (j > m)) return 0;

        int res = 0;
        while (i){
            int k = j;
            while (k){
                res += tree[i][k];
                k ^= (k & (-k));
            }
            i ^= (i & (-i));
        }
        return res;
    }

    /// Query for sum of the sub-rectangle from upper-left [i,j] to lower-right [k,l]
    int query(int i, int j, int k, int l){
        if (i > k || j > l) return 0;

        int res = query(k, l) - query(i - 1, l) + query(i - 1, j - 1) - query(k, j - 1);
        return res;
    }
};

/// 2D Fenwick tree, Range updates and point queries
class Fenwick2D{
    public:
    int n, m, tree[MAX][MAX];

    Fenwick2D(){
    }

    Fenwick2D(int a, int b){
        clr(tree);
        n = a, m = b;
    }

    /// Add v to the sub-rectangle from upper-left [i,j] to lower-right [n,n]
    void update(int i, int j, int v){
        if ((i < 0) || (j < 0) || (i > n) || (j > m)) return;

        while (i <= n){
            int k = j;
            while (k <= m){
                tree[i][k] += v;
                k += (k & (-k));
            }
            i += (i & (-i));
        }
    }

    /// Add v to the sub-rectangle from upper-left [i,j] to lower-right [k,l]
    void update(int i, int j, int k, int l, int v){
        if (i > k || j > l) return;

        update(i, j, v);
        update(k + 1, j, -v);
        update(k + 1, l + 1, v);
        update(i, l + 1, -v);
    }

    /// Query for the value at index [i][j]
    int query(int i, int j){
        int res = 0;
        while (i){
            int k = j;
            while (k){
                res += tree[i][k];
                k ^= (k & (-k));
            }
            i ^= (i & (-i));
        }
        return res;
    }
};

/// 2D Fenwick tree, Range updates and range queries
class Fenwick2D{
    public:
    int n, m;
    long long tree[4][MAX][MAX];

    Fenwick2D(){
    }

    Fenwick2D(int a, int b){
        clr(tree);
        n = a, m = b;
    }

    /// Add v to the sub-rectangle from upper-left [p,q] to lower-right [n,n]
    void update(int p, int q, long long v){
        if ((p < 0) || (q < 0) || (p > n) || (q > m)) return;

        int i = p, c = p - 1, d = q - 1;

        while (i <= n){
            int j = q;
            while (j <= m){
                tree[0][i][j] += v;
                tree[1][i][j] += (v * d);
                tree[2][i][j] += (v * c);
                tree[3][i][j] += (v * c * d);
                j += (j & (-j));
            }
            i += (i & (-i));
        }
    }

    /// Query for sum of the sub-rectangle from upper-left [p,q] to lower-right [n,n]
    long long query(int p, int q){
        int i, j;
        long long x, y, z, c, d, res;

        i = p, x = y = z = 0;
        while (i){
            j = q, c = d = 0;
            while (j){
                c += tree[0][i][j];
                d += tree[1][i][j];
                y += tree[2][i][j];
                z += tree[3][i][j];
                j ^= (j & (-j));
            }
            i ^= (i & (-i));
            x += ((c * q) - d);
        }

        res = (x * p) - (y * q) + z;
        return res;
    }

    /// Add v to the sub-rectangle from upper-left [i,j] to lower-right [k,l]
    void update(int i, int j, int k, int l, long long v){
        update(i, j, v);
        update(k + 1, j, -v);
        update(k + 1, l + 1, v);
        update(i, l + 1, -v);
    }

    /// Query for sum of the sub-rectangle from upper-left [i,j] to lower-right [k,l]
    long long query(int i, int j, int k, int l){
        if (i > k || j > l) return 0;

        long long res = query(k, l) - query(i - 1, l) + query(i - 1, j - 1) - query(k, j - 1);
        return res;
    }
};
