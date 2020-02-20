const int maxN = 50000+5, maxM = 50000+5;
struct HopcroftKarp {
  int n, vis[maxN], lev[maxN], ml[maxN], mr[maxM];
  vector<int> edge[maxN]; //edges for lft art only
  HopcroftKarp(int n) : n(n) {//n=nodes in lft prt
    for (int i = 1; i <= n; ++i) edge[i].clear();
  }
  void add(int u, int v) {edge[u].push_back(v);}
  bool dfs(int u) {
    vis[u] = true;
    for(auto it=edge[u].begin();it!=edge[u].end();
                                            ++it){
      int v = mr[*it];
      if (v==-1 || (!vis[v] && lev[u] < lev[v] &&
                                         dfs(v))){
        ml[u] = *it; mr[*it] = u; return true;
      }
    }
    return false;
  }
  int matching() { // n for left
    memset(vis, 0,sizeof vis);
    memset(lev,0,sizeof lev);
    memset(ml, -1, sizeof ml);
    memset(mr, -1, sizeof mr);
    for (int match = 0;;) {
      queue<int> que;
      for (int i = 1; i <= n; ++i) {
        if (ml[i] == -1) lev[i] = 0, que.push(i);
        else lev[i] = -1;
      }
      while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (auto it = edge[u].begin();
                      it != edge[u].end(); ++it) {
          int v=mr[*it];
          if(v!=-1 && lev[v] < 0)
            lev[v] = lev[u]+1, que.push(v);
        }
      }
      for (int i = 1; i <= n; ++i) vis[i] = false;
      int d = 0;
      for (int i=1;i<=n;++i)
        if(ml[i]==-1 && dfs(i)) ++d;
      if (d == 0) return match;
      match += d;
    }
  }
};
