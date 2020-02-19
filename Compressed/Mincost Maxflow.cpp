///0 Based, dir graphs (for undir add two diredge)
namespace mcmf{
  const int N = 1000010; const LL INF = 1LL << 60;
  LL cap[N], flow[N], cost[N], dis[N];
  int n,m,s,t,Q[10000010];
  int adj[N],link[N],last[N],from[N],vis[N];
  void init(int nodes, int source, int sink){
    m = 0, n = nodes, s = source, t = sink;
    for (int i = 0; i <= n; i++) last[i] = -1;
  }
  void addEdge(int u,int v,LL c,LL w){
    adj[m]=v, cap[m]=c, flow[m]=0, cost[m]=+w,
    link[m]=last[u], last[u]=m++;
    adj[m]=u, cap[m]=0, flow[m]=0, cost[m]=-w,
    link[m]=last[v], last[v]=m++;
  }
  bool spfa(){
    int i, j, x, f = 0, l = 0;
    for (i=0; i<=n; i++) vis[i] = 0, dis[i] = INF;
    dis[s] = 0, Q[l++] = s;
    while (f < l){
      i = Q[f++];
      for (j = last[i]; j != -1; j = link[j]){
        if (flow[j] < cap[j]){
          x = adj[j];
          if (dis[x] > dis[i] + cost[j]){
            dis[x] = dis[i]+cost[j], from[x] = j;
            if (!vis[x]){
              vis[x] = 1;
              if (f && rand() & 7) Q[--f] = x;
              else Q[l++] = x;
            }
          }
        }
      }
      vis[i] = 0;
    }
    return (dis[t] != INF);
  }
  pair <LL, LL> solve(){
    int i, j; LL mincost = 0, maxflow = 0;
    while (spfa()){
      LL aug = INF;
      for(i=t,j=from[i];i!=s;i=adj[j^1],j=from[i])
        aug = min(aug, cap[j]-flow[j]);
      for(i=t,j=from[i];i!=s;i=adj[j^1],j=from[i])
        flow[j] += aug, flow[j ^ 1] -= aug;
      maxflow += aug, mincost += aug * dis[t];
    }
    return make_pair(mincost, maxflow);
  }
}
