const int mx = 1e5+5;//max(#of ej,#of nd)
namespace BCT {
  bool isCutPoint[mx] ; int n , m ;
  int low[mx],pre[mx],cnt2vcc,used[mx];
  vector <int> biComp[mx] ;
  struct Edge{ int v , id ;};
  vector<Edge> g[mx];  stack<int> stk;
  vector<int> bridges; // for bridges
  void init(int _n, int _m){
    n = _n ; m = _m ;
    for(int i=1 ; i<=n ; i++)
      g[i].clear(),biComp[i].clear();
      bridges.clear() ; /* for bridge */
  }
  void addEdge( int u, int v, int id ){
    g[u].pb({v,id}); g[v].pb({u,id});
  }
  void makeComponent( int edgeId ){
    ++cnt2vcc ;
    while( stk.size() != 0 ){
      biComp[cnt2vcc].pb( stk .top() ) ;
      if(stk.top()==edgeId) {
        stk.pop();break;
      }
      stk.pop() ;
    }
  }
  int dfs(int u,int par, int edgeId,
          int &cnt) {
    if(!used[edgeId] && edgeId !=0) {
      used[edgeId]=true;stk.push(edgeId);
    }
    if(pre[u] != -1) {
      low[par] = min(low[par],pre[u]);
      return low[par];
    }
    pre[u] = ++cnt; low[u] = pre[u];
    int i; bool hasChild = false;
    for(i=0; i<g[u].size(); i++) {
      if(g[u][i].id == edgeId) continue;
      int v = g[u][i].v;
      if(dfs(v,u,g[u][i].id,cnt) < 0) {
        low[u] = min(low[u], low[v]);
        if(low[v] == pre[v]) {
          bridges.pb(g[u][i].id) ;
        }
        if(!par?hasChild:low[v]>=pre[u]){
          isCutPoint[u] = true;
          makeComponent(g[u][i].id);
        }
        hasChild = true;
      }
    }
    if(par==0 && stk.size()!=0)
      makeComponent(-1);
    return -1 ;
  }
  int find2VCC() {
    int i,j, cnt = 0; cnt2vcc = 0;
    for(i=1; i<=m; i++) used[i] = false;
    for(i=1; i<=n; i++) {
      isCutPoint[i] = false; pre[i] = -1;
    }
    for(i=1; i<=n ; i++) {
      if(pre[i] == -1) dfs(i,0,0,cnt) ;
    }
  }
}
//BCT::init(n,m); BCT::addEdge(u,v,i) ;
//BCT::find2VCC();int cnt=BCT::cnt2vcc;