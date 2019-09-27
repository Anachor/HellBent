#include <bits/stdtr1c++.h>

#define MAX 1000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

/// Fenwick tree, Point updates and range queries
class Fenwick{
    public:
    int n, tree[MAX];

    Fenwick(){
    }

    Fenwick(int m){
        n = m;
        for (int i = 1; i <= n; i++) tree[i] = 0;
    }

    /// Add v to index p
    void update(int p, int v){
        while (p <= n){
            tree[p] += v;
            p += (p & (-p));
        }
    }

    /// Returns sum from index [1:p]
    int query(int p){
        int res = 0;
        while (p){
            res += tree[p];
            p ^= (p & (-p));
        }
        return res;
    }

    /// Returns sum from index [l:r]
    int query(int l, int r){
        if (l > r) return 0;
        return (query(r) - query(--l));
    }
};

/// Fenwick tree, Range updates and point queries
class Fenwick{
    public:
    int n, tree[MAX];

    Fenwick(){
    }

    Fenwick(int m){
        n = m;
        for (int i = 1; i <= n; i++) tree[i] = 0;
    }

    /// Add v to index [p:n]
    void update(int p, int v){
        while (p <= n){
            tree[p] += v;
            p += (p & (-p));
        }
    }

    /// Add v to index [l:r]
    void update(int l, int r, int v){
        if (l > r) return;
        update(l, v);
        update(r + 1, -v);
    }

    /// Returns value of index p
    int query(int p){
        int res = 0;
        while (p){
            res += tree[p];
            p ^= (p & (-p));
        }
        return res;
    }
};

/// Fenwick tree, Range updates and range queries
class Fenwick{
    public:
    int n;
    long long tree[MAX], temp[MAX];

    Fenwick(){
    }

    Fenwick(int m){
        n = m;
        for (int i = 1; i <= n; i++) tree[i] = temp[i] = 0;
    }

    void update(long long* tree, int p, long long v){
        while (p <= n){
            tree[p] += v;
            p += (p & (-p));
        }
    }

    /// Add v to index [l:r]
    void update(int l, int r, long long v){
        if (l > r) return;
        update(tree, l, v);
        update(tree, r + 1, -v);
        update(temp, l, v * (l - 1));
        update(temp, r + 1, (-v) * r);
    }

    long long query(long long* tree, int p){
        long long res = 0;
        while (p){
            res += tree[p];
            p ^= (p & (-p));
        }
        return res;
    }

    /// Returns sum from index [1:p]
    long long query(int p){
        return ((query(tree, p) * p) - query(temp, p));
    }

    /// Returns sum from index [l:r]
    long long query(int l, int r){
        if (l > r) return 0;
        return (query(r) - query(--l));
    }
};

int main(){

}
