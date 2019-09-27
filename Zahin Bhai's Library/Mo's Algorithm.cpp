#include <bits/stdtr1c++.h>

#define MAXN 200010
#define MAXQ 200010
#define MAXV 1000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

using namespace std;

/// 0 based index for arrays and queries

const int block_size = 633;

long long res, out[MAXQ];
int n, q, ar[MAXN], freq[MAXV];

struct query{
    int l, r, d, i;

    inline query() {}
    inline query(int a, int b, int c){
        i = c;
        l = a, r = b, d = l / block_size;
    }

    inline bool operator < (const query& other) const{
        if (d != other.d) return (d < other.d);
        return ((d & 1) ? (r < other.r) : (r > other.r));
    }
} Q[MAXQ];

inline void insert(int i){
    res += (long long)ar[i] * (1 + 2 * freq[ar[i]]++);
}

inline void erase(int i){
    res -= (long long)ar[i] * (1 + 2 * --freq[ar[i]]);
}

inline void run(){ /// hash = 812195
    sort(Q, Q + q);
    int i, l, r, a = 0, b = 0;

    for (res = 0, i = 0; i < q; i++){
        l = Q[i].l, r = Q[i].r;
        while (a > l) insert(--a);
        while (b <= r) insert(b++);
        while (a < l) erase(a++);
        while (b > (r + 1)) erase(--b);
        out[Q[i].i] = res;
    }
    for (i = 0; i < q; i++) printf("%lld\n", out[i]);
}

int main(){
    int n, i, j, k, a, b;

    scanf("%d %d", &n, &q);
    for (i = 0; i < n; i++) scanf("%d", &ar[i]);
    for (i = 0; i < q; i++){
        scanf("%d %d", &a, &b);
        Q[i] = query(a - 1, b - 1, i);
    }

    run();
    return 0;
}
