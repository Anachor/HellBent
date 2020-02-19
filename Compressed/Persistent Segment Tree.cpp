int a[N], root[N];
struct node { int sm, l, r;} node[N*LOG];
int tot_nodes = 0;
int upd(int cn, int b, int e, int i, int val) {
  int cur = ++tot_nodes;
  if(b==e) {
    node[cur].sm=node[cn].sm + val; return cur;
  }
  int mid = (b+e)/2;
  if (i <= mid) {
    node[cur].l = upd(node[cn].l, b, mid, i, val);
    node[cur].r = node[cn].r;
  }
  else {
    node[cur].r = upd(node[cn].r, mid+1,e,i, val);
    node[cur].l = node[cn].l;
  }
  node[cur].sm = node[node[cur].l].sm
                           + node[node[cur].r].sm;
  return cur;
}
int query(int cn , int b , int e , int i, int j) {
  if (b > j or e < i or !cn) return 0 ;
  if (b >= i and e <= j) return node[cn].sm;
  int mid = (b+e)/2;
  return query(node[cn].l,b,mid,i,j)
        + query(node[cn].r,mid+1,e,i,j);
}
