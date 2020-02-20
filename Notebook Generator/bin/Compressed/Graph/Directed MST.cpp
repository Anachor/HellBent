struct Edge{
  int u, v, w; Edge(){}
  Edge(int a, int b, int c){ u = a, v = b, w = c;}
};
//Directed minimum spanning tree in O(n * m)
//Mks a rooted tree of min weight frm da root node
//Returns -1 if no solution from root
int directed_MST(int n, vector<Edge> E, int root){
  const int INF = (1 << 30) - 30;
  int i, j, k, l, x, y, res = 0;
  vector<int> cost(n),parent(n),label(n),comp(n);
  for (; ;){
    for (i = 0; i < n; i++) cost[i] = INF;
    for (auto e: E){
      if (e.u != e.v && cost[e.v] > e.w){
        cost[e.v] = e.w; parent[e.v] = e.u;
      }
    }
    cost[root] = 0;
    for (i = 0; i < n && cost[i] != INF; i++){};
    if (i != n) return -1; /// No solution
    for (i = 0, k = 0; i < n; i++) res += cost[i];
    for (i = 0; i < n; i++) label[i] = comp[i]=-1;
    for (i = 0; i < n; i++){
      for(x=i;x!=root&&comp[x]==-1;x=parent[x])
        comp[x]=i;
      if (x != root && comp[x] == i){
        for (k++;label[x]==-1;x=parent[x])
          label[x]=k-1;
      }
    }
    if (k == 0) break;
    for (i = 0; i < n; i++){
      if (label[i] == -1) label[i] = k++;
    }
    for (auto &e: E){
      x = label[e.u], y = label[e.v];
      if (x != y) e.w -= cost[e.v];
      e.u = x, e.v = y;
    }
    root = label[root], n = k;
  }
  return res;
}
