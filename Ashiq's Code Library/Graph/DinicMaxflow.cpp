#define MAXN 30010
#define clr(ar) memset(ar, 0, sizeof(ar))
/*Dinic's algorithm for directed graphs (0 based index for
graphs). For undirected graphs, just add two directed edges*/
const long long INF = (~0ULL) >> 1;
namespace flow{
  struct Edge{
  int u, v; long long cap, flow;
  Edge(){}
    Edge(int a, int b, long long c, long long f){
      u = a, v = b, cap = c, flow = f;
    }
  };
  vector <int> adj[MAXN]; vector <struct Edge> E;
  int n, s, t, ptr[MAXN], len[MAXN], dis[MAXN], Q[MAXN];
  inline void init(int nodes, int source, int sink){
    clr(len); E.clear();
    n = nodes, s = source, t = sink;
    for (int i = 0; i < MAXN; i++) adj[i].clear();
  }
    /// Adds a directed edge with capacity c
  inline void addEdge(int a, int b, long long c){
    adj[a].push_back(E.size());
    E.push_back(Edge(a, b, c, 0));
    len[a]++; adj[b].push_back(E.size());
    E.push_back(Edge(b, a, 0, 0)); len[b]++;
  }

  inline bool bfs(){
    int i, j, k, id, f = 0, l = 0;
    memset(dis, -1, sizeof(dis[0]) * n);
    dis[s] = 0, Q[l++] = s;
    while (f < l && dis[t] == -1){
      i = Q[f++];
      for (k = 0; k < len[i]; k++){
        id = adj[i][k];
        if (dis[E[id].v] == -1 && E[id].flow < E[id].cap){
          Q[l++] = E[id].v; dis[E[id].v] = dis[i] + 1;
        }
      }
    }
    return (dis[t] != -1);
  }
  long long dfs(int i, long long f){
    if (i == t || !f) return f;
    while (ptr[i] < len[i]){
      int id = adj[i][ptr[i]];
      if (dis[E[id].v] == dis[i] + 1){
      long long x = dfs(E[id].v, min(f, E[id].cap - E[id].flow));
        if (x){
          E[id].flow += x, E[id ^ 1].flow -= x;
          return x;
        }
      }
      ptr[i]++;
    }
    return 0;
  }

  long long dinic(){
    long long res = 0;
    while (bfs()){
      memset(ptr, 0, n * sizeof(ptr[0]));
      while (long long f = dfs(s, INF)) {
        res += f;
      }
    }
    return res;
  }
}
