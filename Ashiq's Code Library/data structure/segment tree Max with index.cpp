#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2e5 + 100, inf = 1e9 + 100;
int tree[4*N];
int a[N];

/// max in a range - keeps index
/// initiate a[0] with -inf

void build (int cn,int b,int e) {
    if (b == e) {
        tree[cn] = b;
        return ;
    }
    int lc = 2*cn , rc = lc+1 , mid = (b+e)/2;
    build(lc,b,mid);
    build(rc,mid+1,e) ;
    if(a[tree[lc]] > a[tree[rc]]) tree[cn] = tree[lc];
    else tree[cn] = tree[rc];
}

int query (int cn , int b , int e , int i ,int j) {
    if (b > j or e < i) return 0;
    if (b >= i and e <= j) {
        return tree[cn];
    }
    int lc = 2*cn , rc = lc + 1 , mid = (b+e)/2;
    int idx1 = query(lc, b, mid, i, j), idx2 = query(rc, mid+1, e, i, j);
    if(a[idx1] > a[idx2]) return idx1;
    return idx2;
}

int main() {
    ios::sync_with_stdio(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a[0] = -inf;
    build(1,1,n);
}

