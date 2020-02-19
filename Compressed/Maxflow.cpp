/* 0 based for directed graphs */
const LL INF = (~0ULL) >> 1,N = 30010;
namespace flow{
  struct Edge{
  int u, v; LL cap, flow;
  Edge(){}
    Edge(int a, int b, LL c, LL f){
      u = a, v = b, cap = c, flow = f;
    }
  };
  vector<int> adj[N]; vector<Edge> E;
  int n, s, t, ptr[N],len[N],dis[N],Q[N];
  void init(int nodes,int src,int sink){
    clr(len); E.clear();
    n = nodes, s = src, t = sink;
    for(int i=0;i<N;i++) adj[i].clear();
  }
  void addEdge(int a, int b, LL c){
    adj[a].push_back(E.size());
    E.push_back(Edge(a, b, c, 0));
    len[a]++;adj[b].push_back(E.size());
    E.push_back(Edge(b,a,0,0));len[b]++;
  }
  bool bfs(){
    int i, j, k, id, f = 0, l = 0;
    memset(dis, -1, sizeof(dis[0]) * n);
    dis[s] = 0, Q[l++] = s;
    while (f < l && dis[t] == -1){
      i = Q[f++];
      for (k = 0; k < len[i]; k++){
        id = adj[i][k];
        if(dis[E[id].v]==-1 &&
           E[id].flow < E[id].cap){
          Q[l++] = E[id].v;
          dis[E[id].v] = dis[i] + 1;
        }
      }
    }
    return (dis[t] != -1);
  }
  LL dfs(int i, LL f){
    if (i == t || !f) return f;
    while (ptr[i] < len[i]){
      int id = adj[i][ptr[i]];
      if (dis[E[id].v] == dis[i] + 1){
        LL ff = E[id].cap - E[id].flow;
        LL x = dfs(E[id].v, min(f,ff));
        if (x) {
          E[id].flow+=x,E[id^1].flow-=x;
          return x;
        }
      }
      ptr[i]++;
    }
    return 0;
  }
  LL dinic(){
    LL res = 0;
    while (bfs()){
      memset(ptr, 0, n * sizeof(ptr[0]));
      while (LL f = dfs(s, INF)) {
        res += f;
      }
    }
    return res;
  }
}
