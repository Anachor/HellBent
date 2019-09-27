#include <bits/stdtr1c++.h>

#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

pair<int, int> val[MAX];
int n, ar[MAX], pos[MAX];
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

void build(){
    for (int i = 1; i <= n; i++) val[i] = make_pair(ar[i], i);
    sort(val + 1, val + 1 + n);
    for (int i = 1; i <= n; i++) pos[i] = val[i].second;
    merge_sort_tree(1, 1, n, pos);
}

int query(int l, int r, int k){ /// hash = 939184
    int m, c, a = 1, b = n, idx = 1;

    while (a != b){
        m = (a + b) >> 1, idx <<= 1;
        c = upper_bound(tree[idx].begin(), tree[idx].end(), r) - lower_bound(tree[idx].begin(), tree[idx].end(), l);
        if (c >= k) b = m;
        else k -= c, idx |= 1, a = ++m;
    }
    return val[a].first;
}

int main(){
    int i, j, k, x, q, l, r;

    while (scanf("%d %d", &n, &q) != EOF){
        for (i = 1; i <= n; i++) scanf("%d", &ar[i]);
        build();

        while (q--){
            scanf("%d %d %d", &l, &r, &k);
            printf("%d\n", query(l, r, k));
        }
    }
    return 0;
}
