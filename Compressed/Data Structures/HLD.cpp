namespace hld{
  int in[maxn] , out[maxn] , sub[maxn] , t = 1,
   nxt[maxn] , depth[maxn], par[maxn] , n ;
  vector <int> g[maxn] ;
  void init(int _n){
    n = _n ;
    for(int i=0 ; i<=n ; i++) g[i].clear() ;
  }
  void addEdge(int u, int v){
    g[u].pb(v) ; g[v].pb(u) ;
  }
  void dfsSZ(int u){
    sub[u] = 1 ;
    for(int i=0 ; i<g[u].size() ; i++){
      int v = g[u][i] ;
      for(int j=0 ; j<g[v].size() ; j++){
        if( g[v][j] == u ){
          g[v].erase(g[v].begin()+j);
          break ;
        }
      }
      dfsSZ(v) ;
      sub[u] += sub[v] ;
    if(sub[v]>sub[g[u][0]])swap(g[u][0],g[u][i]);
    }
  }
  void dfsHLD(int u){
    in[u] = ++t ;
    for(int i=0 ; i<g[u].size() ; i++){
      int v = g[u][i] ; par[v] = u ;
      depth[v] = depth[u] + 1 ;
      if( i==0 ) nxt[v] = nxt[u] ;
      else nxt[v] = v ;
      dfsHLD(v) ;
    }
    out[u] = t ;
  }
  void preprocess(int root){
    dfsSZ(root) ; t = 0 ; nxt[root] = root ;
    depth[root] = 1 ; dfsHLD(root) ;
  }
  int hldQuery( int u , int v ){
    int ans = -INF ;
    while( nxt[u] != nxt[v] ){
      if(depth[nxt[u]]<depth[nxt[v]]){
    ans=max(ans,query(1,1,n,in[nxt[v]],in[v]));
// do your thing here ( from in[v] to in[ nxt[v]])
        v = par[nxt[v]];
      }
      else{
    ans=max(ans,query(1,1,n,in[nxt[u]],in[u]));
// do your thing here(from in[u] to in[nxt[u]])
        u = par[nxt[u]];
      }
    }
    int lc ;
    if( depth[u] > depth[v] ) swap(u,v) ;
    lc = u ;
    //here lc is the lca
    //if you are working on node ,
    //not on edge, then update/query upto u also
    //otherwise update/query from in[u]+1 to in[v]
    ans = max( ans , query(1,1,n,in[u]+1,in[v]) );
    return ans ;
  }
  void hldUpdate( int u , int v , int val ){
    while( nxt[u] != nxt[v] ){
      if( depth[ nxt[u] ] < depth[ nxt[v] ] ){
        update(1,1,n,in[ nxt[v] ] , in[v] , val );
// do you thing here ( from in[v] to in[ nxt[v] ])
        v = par[ nxt[v] ];
      }
      else{
        update(1,1,n,in[ nxt[u] ] , in[u] , val );
// do your thing here (from in[u] to in[nxt[u]])
        u = par[ nxt[u] ] ;
      }
    }
    int lc ;
    if( depth[u] > depth[v] ) swap(u,v) ;
    lc = u ;
    //here lc is the lca
    //if you are working on node , not on edge,
    //then update/query upto u also
    //otherwise update/query from in[u]+1 to in[v]
    update(1,1,n,in[u]+1,in[v],val) ;
    return ;
  }
}
