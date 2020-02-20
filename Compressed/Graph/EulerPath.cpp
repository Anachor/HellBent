int c[maxn] , d[maxn] ;
map< int , multiset<int> > g ; map <int,int> vis ;
void dfs1(int u){
  vis[u] = 1 ;
  for( auto v : g[u] )
    if( vis.find(v) == vis.end() ) dfs1(v) ;
}
//just call dfs2 with the node you want to start
//your path at first you need to make sure,
//the graph is connected and euler path exists
vector <int> ans ;
void dfs2(int u){
  while( (int)g[u].size() !=0 ){
    int v = *g[u].begin() ;
    g[u].erase(g[u].find(v));
    g[v].erase(g[v].find(u)); dfs2(v) ;
  }
  ans.pb(u) ;
}
int main(){
  int n; scanf("%d",&n) ;
  for(int i=1 ; i<n ; i++) scanf("%d",&c[i]) ;
  for(int i=1 ; i<n ; i++) scanf("%d",&d[i]) ;
  for(int i=1 ; i<n ; i++)  {
    if( c[i] > d[i] ){
      printf("-1\n"); return 0 ;
    }
    g[c[i]].insert(d[i]); g[d[i]].insert(c[i]);
  }
  int src = c[1] , cnt = 0 ;
  for( auto it : g ){
    if( (int)it.second.size() & 1 ){
      cnt++ ; src = it.first ;
    }
  }
  dfs1( src ) ;
  if(vis.size()!=g.size()||(cnt!=0&&cnt!=2)){
    printf("-1\n") ;
    return 0 ;
  }
  //call for printing euler path
  dfs2(src) ;
  for(int i=0 ; i<ans.size() ; i++){
    printf("%d",ans[i]) ;
    if( i == (int)ans.size() - 1 ) printf("\n") ;
    else printf(" ") ;
  }
}
