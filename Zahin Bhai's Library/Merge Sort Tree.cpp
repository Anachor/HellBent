#include <bits/stdtr1c++.h>

#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

int n, ar[MAX];
vector<int> tree[MAX << 2];

void merge_sort_tree(int idx, int a, int b, int* ar){ /// hash = 974987
    int p = idx << 1, q = p | 1, c = (a + b) >> 1, d = c + 1;
    int i = 0, j = 0, k = 0, u = c - a + 1, v = b - d + 1, len = b - a + 1;

    tree[idx].resize(len, 0);
    if (a == b){
        tree[idx][0] = ar[a];
        return;
    }

    merge_sort_tree(p, a, c, ar);
    merge_sort_tree(q, d, b, ar);
    while (len--){
        if (i == u) tree[idx][k++] = tree[q][j++];
        else if (j == v) tree[idx][k++] = tree[p][i++];
        else if (tree[p][i] < tree[q][j]) tree[idx][k++] = tree[p][i++];
        else tree[idx][k++] = tree[q][j++];
    }
}

/// Count of numbers <= k in the segment l-r
inline int query(int idx, int a, int b, int l, int r, int k){ /// hash = 476541
    int p = idx << 1, q = p | 1;
    int c = (a + b) >> 1, d = c + 1;

    if (a == l && b == r){
        if (tree[idx][0] > k) return 0;
        else return upper_bound(tree[idx].begin(), tree[idx].end(), k) - tree[idx].begin();
    }
    if (r <= c) return query(p, a, c, l, r, k);
    else if (l >= d) return query(q, d, b, l, r, k);
    else return query(p, a, c, l, c, k) + query(q, d, b, d, r, k);
}

int main(){

}
