#include <bits/stdc++.h>
using namespace std;

/*
    range update : Add X to l to r
    range query : sum l to r
*/

const int N = 1e5 + 5;

int tree[4*N], lazy[4*N], a[N];

void init() {
    memset(tree,0,sizeof tree);
    memset(lazy,0,sizeof lazy);
}

void build (int cn,int b,int e) {
    if (b == e) {
        tree[cn] = a[b];
        return;
    }
    int lc = 2*cn, rc = lc+1, mid = (b+e)/2;
    build(lc,b,mid);
    build(rc,mid+1,e);
    tree[cn] = tree[lc] + tree[rc];
}

void relax (int cn, int b, int e) {
    if (lazy[cn]) {
        tree[cn] += (e-b+1)*lazy[cn] ;
        if (b != e) {
            lazy[2*cn] += lazy[cn] ;
            lazy[2*cn + 1] += lazy[cn] ;
        }
        lazy[cn] = 0;
    }
}

void upd (int cn, int b, int e, int i, int j, int add) {
    relax(cn,b,e);
    if (b > j or e < i) {
        return;
    }
    int lc = 2*cn , rc = lc + 1 , mid = (b+e)/2;
    if (b >= i and e <= j) {
        lazy[cn] += add;
        relax(cn,b,e);
        return;
    }
    upd(lc,b,mid,i,j,add);
    upd(rc,mid+1,e,i,j,add);
    tree[cn] = tree[lc] + tree[rc];
}

int query (int cn, int b, int e, int i, int j) {
    relax(cn,b,e);
    if (b > j or e < i) return 0;
    if (b >= i and e <= j) {
        return tree[cn];
    }
    int lc = 2*cn, rc = lc + 1, mid = (b+e)/2;
    return query(lc,b,mid,i,j) + query(rc,mid+1,e,i,j);
}

int main () {

    return 0;
}
