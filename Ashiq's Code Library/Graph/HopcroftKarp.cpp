struct Hopcroft_Karp { /// // N = left node + right node
    const int NIL=0,INF=(1<<28),match[N],dist[N],n,m;
    vector <int> G[N] ;
    void init(int lft , int rgt) {
        n = lft , rgt = m ;
        for (int i = 0 ; i <= n+m+1 ; i++) G[i].clear() ;
    }
    void addEdge(int u , int v){ //u = left node from 1 to n
        G[u].push_back(v+n) ;//v = right node 1 to m
    }
    bool bfs(){
        queue <int> Q;
        for(int i = 1; i <= n ;i++) {
            if(match[i]==NIL) dist[i] = 0,Q.push(i);
            else dist[i] = INF;
        }
        dist[NIL] = INF;
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            if(u!=NIL) {
                for(int i = 0; i < G[u].size(); i++) {
                    int v = G[u][i];
                    if(dist[match[v]]==INF) {
                        dist[match[v]] = dist[u] + 1;
                        Q.push(match[v]);
                    }
                }
            }
        }
        return (dist[NIL]!=INF);
    }
    bool dfs(int u) {
        if(u!=NIL) {
            for(int i = 0; i < G[u].size() ; i++) {
                int v = G[u][i] ;
                if(dist[match[v]] == dist[u]+1) {
                    if(dfs(match[v])) {
                        match[v] = u;
                        match[u] = v;
                        return true;
                    }
                }
            }
            dist[u] = INF;
            return false;
        }
        return true;
    }

    int hopcroft_karp() {
        memset( dist, 0, sizeof dist );
        memset( match, 0, sizeof match );
        int matching = 0 ;
        while(bfs()) {
            for(int i = 1 ; i <= n; i++) {
                if(match[i]==NIL && dfs(i)) {
                    matching++ ;
                }
            }
        }
        return matching;
    }
    void VertexCover(vector<int>&color){///1: in min cover
      hopcroft_karp();
      vector< vector<int> > g(R+L+1) ; queue <int> Q;
      vector <int> vis(L+R+1,0) ;
      for(int u = 1 ; u <= L ; u++) {
        if (match[u]==0) Q.push(u) , vis[u] = 1;
        for(int i = 0 ; i < G[u].size(); i++) {
          int v = G[u][i] ;
          if (match[u] == v) g[v].push_back(u);
          else g[u].push_back(v);
        }
      }
      while(Q.size()) {
        int u = Q.front() ; Q.pop();
        for(int i = 0 ; i < g[u].size() ; i++) {
          int v = g[u][i] ;
          if (vis[v] == 0) vis[v] = 1 , Q.push(v);
        }
      }
      color.resize(R+L+1) ;
      for(int i = 1 ; i <= L ; i++) color[i] = (!vis[i]);
      for(int i = L+1 ; i <= L+R ; i++) color[i] = vis[i];
    }
};
/// call init() , then addEdge , then hopcroft_karp()
