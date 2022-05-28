#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 100;

int tr[4*N], a[N]; /// be careful with overflow
int inf = 2e9;

void build (int cn , int b , int e) {
    if (b == e) {
        tr[cn] = a[b];
        return;
    }
    int lc = 2*cn, rc = lc+1, mid = (b+e)/2;
    build(lc,b,mid);
    build(rc,mid+1,e);
    tr[cn] = min(tr[lc],tr[rc]);
}


void upd (int cn , int b , int e , int i, int x) {
    if (b > i or e < i) {
        return;
    }
    int lc = 2*cn, rc = lc + 1, mid = (b+e)/2;
    if (b >= i and e <= i) {
        tr[cn] = x;
        return;
    }
    upd(lc,b,mid,i,x);
    upd(rc,mid+1,e,i,x);
    tr[cn] = min(tr[lc],tr[rc]);
}


int query (int cn , int b , int e , int i ,int j) {
    if (b > j or e < i) return inf;
    if (b >= i and e <= j) {
        return tr[cn];
    }
    int lc = 2*cn, rc = lc + 1, mid = (b+e)/2;
    return min(query(lc,b,mid,i,j),query(rc,mid+1,e,i,j));
}

int main() {
    return 0;
}

