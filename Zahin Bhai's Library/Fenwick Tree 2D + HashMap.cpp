/// 2D Fenwick Tree with HashMap
/// When N = 10^5, runs in 0.8 seconds in codeforces server for random cases
/// When N = 2 * 10^5, runs in 2.00 seconds in codeforces server for random cases

#include <bits/stdtr1c++.h>

#define MAX 200010
#define HMOD 16777215
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

int n, m, tree[HMOD + 71235];
long long hashmap[HMOD + 71235];

inline void add(int i, int j, int v){
    long long h = (((long long)i * 1000003) + j) + 917921;
    int k = h & HMOD;
    while (hashmap[k] && hashmap[k] != h) k++;
    hashmap[k] = h, tree[k] += v;
}

inline int find(int i, int j){
    long long h = (((long long)i * 1000003) + j) + 917921;
    int k = h & HMOD;
    while (hashmap[k] && hashmap[k] != h) k++;
    return (hashmap[k] ? tree[k] : 0);
}

/// Add v to ar[i][j]
inline void update(int i, int j, int v){
    while (i <= n){
        int k = j;
        while (k <= m){
            add(i, k, v);
            k += (k & (-k));
        }
        i += (i & (-i));
    }
}

/// Query for sum of the sub-rectangle from upper-left [i,j] to lower-right [n,n]
inline int query(int i, int j){
    if ((i < 0) || (j < 0) || (i > n) || (j > m)) return 0;

    int res = 0;
    while (i){
        int k = j;
        while (k){
            res += find(i, k);
            k ^= (k & (-k));
        }
        i ^= (i & (-i));
    }
    return res;
}

/// Query for sum of the sub-rectangle from upper-left [i,j] to lower-right [k,l]
inline int query(int i, int j, int k, int l){
    if (i > k || j > l) return 0;

    int res = query(k, l) - query(i - 1, l) + query(i - 1, j - 1) - query(k, j - 1);
    return res;
}

int main(){
    clock_t start = clock();
    int q, i, j, k, l, x, y, z;

    n = 200000;
    m = n, q = n;

    long long res = 0;
    while (q--){
        int flag = ran(0, 1);

        if (flag == 0){
            i = ran(1, n), k = ran(i, n);
            j = ran(1, m), l = ran(j, m);
            res += query(i, j, k, l);
        }

        if (flag == 1){
            i = ran(1, n), j = ran(1, m), x = ran(1, 100);
            update(i, j, x);
        }
    }

    printf("%0.5f\n", (clock() - start) / (1.0 * CLOCKS_PER_SEC));
    return 0;
}
