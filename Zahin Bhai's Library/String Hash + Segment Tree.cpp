#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// String Hash with Segment Tree
/// Allows setting range with a character, querying hash of a range in O(log n)
/// String functions uses 0-based index, however segment tree uses 1-based index

namespace strhash{
    #define LET 10 /// Number of distinct letters in string, Set to digits [0-9] by default
    #define ADD 10007 /// Just another prime added randomly to get better hash values :)
    #define MAX 100010

    int P[2][MAX], RD[2][LET][MAX];
    int n, ar[MAX], lazy[MAX * 4];
    const int MOD[] = {2078526727, 2117566807};
    const int BASE[] = {1572872831, 1971536491};

    void build_tree(int idx, int a, int b);

    inline int getval(char ch){ /// Value of a character (without adding ADD)
        return ch - 48; /// Change this for lowercase or uppercase letters
    }

    void precalc(){ /// Call precalc() just once in whole program
        int i, j, k, d;
        P[0][0] = P[1][0] = 1;
        for (i = 1; i < MAX; i++){
            P[0][i] = ((long long) P[0][i - 1] * BASE[0]) % MOD[0];
            P[1][i] = ((long long) P[1][i - 1] * BASE[1]) % MOD[1];
        }

        for (i = 0; i < 2; i++){
            for (d = 0; d < LET; d++){
                k = ADD + d;
                long long x = 0;
                for (j = 1; j <= MAX; j++){
                    x = ((x * BASE[i]) + k) % MOD[i];
                    RD[i][d][j] = x;
                }
            }
        }
    }

    void init(char* str){
        n = strlen(str);
        for (int i = 0; i < n; i++) ar[i + 1] = getval(str[i]) + ADD;
        build_tree(1, 1, n);
    }

    struct Node{
        int H[2];

        inline Node(){
        }

        inline Node(int h1, int h2){
            H[0] = h1, H[1] = h2;
        }
    } tree[MAX << 2];

    inline void propagate(int idx, int a, int b){
        if (lazy[idx]){
            int p = (idx << 1), q = p + 1;
            int c = (a + b) >> 1, d = c + 1, val = lazy[idx];

            if (a != b){
                lazy[p] = lazy[q] = lazy[idx];
                tree[p] = Node(RD[0][val - ADD][c - a + 1], RD[1][val - ADD][c - a + 1]);
                tree[q] = Node(RD[0][val - ADD][b - d + 1], RD[1][val - ADD][b - d + 1]);
            }
            lazy[idx] = 0;
        }
    }

    inline void build_tree(int idx, int a, int b){
        lazy[idx] = 0;
        if (a == b){
            tree[idx].H[0] = tree[idx].H[1] = ar[a];
            return;
        }

        int p = (idx << 1), q = p + 1;
        int c = (a + b) >> 1, d = c + 1;

        build_tree(p, a, c);
        build_tree(q, d, b);

        tree[idx].H[0] = ((tree[p].H[0] * (long long) P[0][b - d + 1]) + tree[q].H[0]) % MOD[0];
        tree[idx].H[1] = ((tree[p].H[1] * (long long) P[1][b - d + 1]) + tree[q].H[1]) % MOD[1];
    }

    inline void update(int idx, int a, int b, int l, int r, int val){
        if (a == l && b == r){
            lazy[idx] = val;
            tree[idx] = Node(RD[0][val - ADD][b - a + 1], RD[1][val - ADD][b - a + 1]);
            propagate(idx, a, b);
            return;
        }

        propagate(idx, a, b);
        int p = (idx << 1), q = p + 1;
        int c = (a + b) >> 1, d = c + 1;

        if (r <= c) update(p, a, c, l, r, val);
        else if (l >= d) update(q, d, b, l, r, val);
        else{
            update(p, a, c, l, c, val);
            update(q, d, b, d, r, val);
        }

        tree[idx].H[0] = ((tree[p].H[0] * (long long) P[0][b - d + 1]) + tree[q].H[0]) % MOD[0];
        tree[idx].H[1] = ((tree[p].H[1] * (long long) P[1][b - d + 1]) + tree[q].H[1]) % MOD[1];
    }

    inline Node query(int idx, int a, int b, int l, int r){
        propagate(idx, a, b);
        int p = (idx << 1), q = p + 1;
        int c = (a + b) >> 1, d = c + 1;

        if (a == l && b == r) return tree[idx];
        if (r <= c) return query(p, a, c, l, r);
        else if (l >= d) return query(q, d, b, l, r);
        else{
            Node x = query(p, a, c, l, c);
            Node y = query(q, d, b, d, r);
            for (int i = 0; i < 2; i++){
                x.H[i] = ((P[i][r - d + 1] * (long long) x.H[i]) + y.H[i]) % MOD[i];
            }
            return x;
        }
    }

    /// Note 0-based index used for string update and gethash
    inline void update(int l, int r, char ch){ /// Sets the sub-string in str[l:r] to ch
        update(1, 1, n, ++l, ++r, getval(ch) + ADD);
    }

    inline long long gethash(int l, int r){
        Node h = query(1, 1, n, ++l, ++r);
        return (h.H[0] << 32) | h.H[1];
    }
}

int main(){

}
