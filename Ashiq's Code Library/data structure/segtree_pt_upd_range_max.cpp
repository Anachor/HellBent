#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5, inf = 2e9;
int tree[4*N], a[N]; /// be careful with overflow

void build (int cn,int b,int e) {
    if (b == e) {
        tree[cn] = a[b];
        return ;
    }
    int lc = 2*cn, rc = lc+1, mid = (b+e)/2;
    build(lc,b,mid);
    build(rc,mid+1,e);
    tree[cn] = max(tree[lc],tree[rc]);
}

void upd (int cn , int b , int e , int i, int add) {
    if (b > i or e < i) {
        return;
    }
    int lc = 2*cn , rc = lc + 1 , mid = (b+e)/2;
    if (b >= i and e <= i) {
        tree[cn] += add;
        return;
    }
    upd(lc,b,mid,i,add);
    upd(rc,mid+1,e,i,add);
    tree[cn] = max(tree[lc],tree[rc]);
}

int query (int cn , int b , int e , int i ,int j) {
    if (b > j or e < i) return -inf;
    if (b >= i and e <= j) {
        return tree[cn];
    }
    int lc = 2*cn, rc = lc + 1, mid = (b+e)/2;
    return max(query(lc,b,mid,i,j), query(rc,mid+1,e,i,j));
}


int main () {

    return 0 ;
}
