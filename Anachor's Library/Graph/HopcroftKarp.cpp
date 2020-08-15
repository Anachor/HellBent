/**
    Hopcroft Karp Weighted Bipartite Matching Algorithm
    Complexity: E sqrt(V)
    Source: Foreverbell ICPC cheat sheet
*/
 
#include<bits/stdc++.h>
using namespace std;
 
const int maxN = 50000+5, maxM = 50000+5;
struct HopcroftKarp {
  int n;
  int vis[maxN], level[maxN], ml[maxN], mr[maxM];
  vector<int> edge[maxN]; // constructing edges for left part only
 
  HopcroftKarp(int n) : n(n) {      // n = nodes in left part
    for (int i = 1; i <= n; ++i) edge[i].clear();
  }
 
  void add(int u, int v) {
    edge[u].push_back(v);
  }
 
  bool dfs(int u) {
    vis[u] = true;
    for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
      int v = mr[*it];
      if (v == -1 || (!vis[v] && level[u] < level[v] && dfs(v))) {
        ml[u] = *it;
        mr[*it] = u;
        return true;
      }
    }
    return false;
  }
 
  int matching() { // n for left
    memset(vis, 0, sizeof vis);
    memset(level, 0, sizeof level);
    memset(ml, -1, sizeof ml);
    memset(mr, -1, sizeof mr);
 
    for (int match = 0;;) {
      queue<int> que;
      for (int i = 1; i <= n; ++i) {
        if (ml[i] == -1) {
          level[i] = 0;
          que.push(i);
        } else level[i] = -1;
      }
      while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
          int v = mr[*it];
          if (v != -1 && level[v] < 0) {
            level[v] = level[u] + 1;
            que.push(v);
          }
        }
      }
      for (int i = 1; i <= n; ++i) vis[i] = false;
      int d = 0;
      for (int i = 1; i <= n; ++i) if (ml[i] == -1 && dfs(i)) ++d;
      if (d == 0) return match;
      match += d;
    }
  }
};
 
 
/// The following code solves SPOJ MATCHING - Fast Maximum Matching
 
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    int n, m, k;
    cin>>n>>m>>k;
 
    HopcroftKarp solver(n);
 
    while(k--) {
        int a, b;
        cin>>a>>b;
        solver.add(a, b);
    }
 
    cout<<solver.matching()<<endl;
}
