#include <bits/stdc++.h>
using namespace std;

/// not tested, persistent segtree for range sum

const int N = 1e5 + 5, LOG = 20;
int a[N], root[N];

struct node {
    int sum, l, r;
}node[N*LOG];

int tot_nodes = 0;

int upd(int cn, int b, int e, int i, int val) {
    int cur = ++tot_nodes;
    if (b == e) {
        node[cur].sum = node[cn].sum + val;
        return cur;
    }
    int mid = (b+e)/2;
    if (i <= mid) {
        node[cur].l = upd(node[cn].l, b, mid, i, val);
        node[cur].r = node[cn].r;
    }
    else {
        node[cur].r = upd(node[cn].r, mid+1, e, i, val) ;
        node[cur].l = node[cn].l;
    }
    node[cur].sum = node[node[cur].l].sum + node[node[cur].r].sum ;
    return cur;
}

int query(int cn , int b , int e , int i, int j) {
    if (b > j or e < i or !cn) return 0 ;
    if (b >= i and e <= j) {
        return node[cn].sum;
    }
    int mid = (b+e)/2;
    return query(node[cn].l,b,mid,i,j) + query(node[cn].r,mid+1,e,i,j);
}

int main () {

    return 0 ;

    /// FOR Creating a New version , root[i] = upd(root[i-1],1,n,idx,val) ;
}
