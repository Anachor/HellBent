vector <int> g[N]; int n, child[N], done[N];
void dfs_size(int u, int par) {
  child[u] = 1;
  for (int v: g[u]) {
    if (done[v] or v == par) continue;
    dfs_size(v, u); child[u] += child[v];
  }
}
int dfs_find_centroid(int u, int par, int sz) {
  for (int v: g[u]) {
    if (!done[v] and v != par and child[v] > sz) {
      return dfs_find_centroid(v,u,sz);
    }
  }
  return u;
}
void solve (int u) {/**problem specific things */}
void dfs_decompose(int u) {
  dfs_size(u, -1);
  int centroid=dfs_find_centroid(u,-1,child[u]/2);
  solve(centroid);
  done[centroid] = 1;
  for (int v : g[centroid]) {
    if (!done[v]) dfs_decompose(v);
  }
}
