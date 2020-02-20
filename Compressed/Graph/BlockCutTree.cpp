namespace BCT{
  const int mx = 100005;//max(edge,node)
  bool isCutPoint[mx] ;
  int low[mx],pre[mx],cnt2vcc,used[mx],Timer = 0;
  vector <int> biComp[mx] ; int n , m ;
  struct Edge{    int v , id ; } ;
  vector <Edge> g[mx]; vector <int> bridges;
  stack  <int> stk ;
  void init(int _n, int _m){
    n = _n ; m = _m ;
    for(int i=1 ; i<=max(n,m) ; i++)
        g[i].clear() , biComp[i].clear() ;
    bridges.clear() ; // for bridge
  }
  void addEdge( int u, int v, int id ){
    g[u].pb( {v,id} ) ; g[v].pb({u,id}) ;
  }
  void dfs(int u , int par ){
    pre[u] = ++Timer;low[u]=pre[u];int chCnt=0;
    for(int i=0 ; i<g[u].size() ; i++){
      int edgeId = g[u][i].id ;
      if( used[ edgeId ] ) continue ;
      used[ edgeId ] = true ; stk.push( edgeId ) ;
      int v = g[u][i].v ;
      if( pre[v]==-1 ){
        dfs( v , u ) ;
        low[u] = min( low[u] , low[v] ) ;
        if(low[v] == pre[v]) bridges.pb(edgeId) ;
        if( low[v] >= pre[u] ){
          cnt2vcc++ ;
          while(stk.size()>0)/*making component*/{
            biComp[cnt2vcc].pb( stk .top() ) ;
            stk.pop() ;
          if(biComp[cnt2vcc].back()==edgeId)break;
          }
          if(par!=0)isCutPoint[u]=true;
            //checking if non-root
        }
        chCnt++ ;
      }
      else low[u] = min( low[u] , pre[v] ) ;
    }
    if(chCnt > 1 && par==0) isCutPoint[u] = true ;
    //checking for root
  }
  int find2VCC(){
    int i , j ; Timer = 0 ;
    for(i=1 ; i<=m ; i++) used[i] = false ;
    for(i=1 ; i<=n ; i++){
      isCutPoint[i] = false ; pre[i] = -1 ;
    }
    cnt2vcc = 0 ;
    for(i=1; i<=n ; i++){
      if( pre[i]==-1 ) dfs(i,0) ;
    }
  }
}
struct Edge{
  int u , v , id ;
}edge[maxn];
int main(){
  //BCT::addEdge(u,v,i);
  BCT::find2VCC() ;
  int cntVcc = BCT::cnt2vcc ; int ans1 ;
  unsigned long long int ans2 ;
  if( cntVcc==1 ){
    ans1 = 2 ; ans2 = (n*(n-1))/2LL ;
  }
  else{
    ans1 = 0 , ans2=1LL ;
    for(i=1; i<=cntVcc ; i++){
      set <int> nodes ;
      for(j=0 ; j<BCT::biComp[i].size() ; j++){
        int id= BCT::biComp[i][j] ;
        nodes.insert(edge[id].u);
        nodes.insert(edge[id].v);
      }
      set<int> :: iterator it = nodes.begin() ;
      int artCnt = 0 ;
      while( it!=nodes.end() ){
        if( BCT::isCutPoint[*it] ) artCnt++ ;
        it++ ;
      }
      if( artCnt==1 ){
        ans1++ ;
        ans2 *= (1LL*(nodes.size() - artCnt )) ;
      }
    }
  }
}
