/*at first take a graph of size 2*n(for each vari
able two nodes). for each clause of type (a or b),
add two diredge !a-->b and !b-->a. if both x_i and
!x_i is in same connected component for some i,
then this equations are unsatisfiable . Otherwise
there is a solution. Assume, f is satisfiable. Now
we want to give values to each var in order to
satisfy f. It can be done with a top sort of
vertices of the graph we made. If !x_i is after
x_i in topological sort, x_i should be FALSE. It
should be TRUE otherwise. say we have equation
with three var x1,x2,x3.(x1 or !x2) and (x2 or x3)
 = 1. so we addx1,x2,x3 and x4(as !x1), x5(!x2)
 and x6(!x3). Add edge x4-->x2,x2-->x1, x5-->x3 ,
 x6-->x2.
you need to pass array to the function findSCC,
in which result will be returned every node will
be given a number, for nodes of a single connected
component the number will be same this number
representing nodes willbe topsorted*/
class SCC{
public:
  vector<int> *g1, *g2; int maxNode, *vis1, *vis2;
  stack<int> st;
  SCC(int MaxNode){
    maxNode = MaxNode ; vis1 = new int[maxNode+2];
    vis2 = new int[maxNode+2] ;
    g1 = new vector<int>[maxNode+2] ;
    g2 = new vector<int>[maxNode+2] ;
  }
  void addEdge(int u,int v){
    g1[u].push_back(v); g2[v].push_back(u);
  }
  void dfs1(int u){
    if(vis1[u]==1) return; vis1[u]=1 ;
    for(int i=0;i<g1[u].size();i++)dfs1(g1[u][i]);
    st.push(u); return;
  }
  void dfs2(int u, int cnt , int *ans){
    if(vis2[u]==1) return ; vis2[u] = 1 ;
    for(int i=0;i<g2[u].size();i++)
      dfs2(g2[u][i],cnt,ans);
    ans[u] = cnt ;
  }
  int findSCC( int *ans ) {
    for(int i=1 ; i<=maxNode ; i++) vis1[i] = 0 ;
    for(int i=1 ; i<=maxNode ; i++)
      if(vis1[i]==0)    dfs1(i);
    int cnt = 0 ;
    for(int i=1 ; i<=maxNode ; i++) vis2[i] = 0 ;
    while( !st.empty() ) {
      int u = st.top() ;
      if(vis2[u]==0) {++cnt ; dfs2(u, cnt, ans);}
      st.pop() ;
    }
    for(int i=1 ; i<=maxNode ; i++) {
      g1[i].clear() ; g2[i].clear() ;
    }
    delete vis1 ; delete vis2 ; return cnt ;
  }
};
