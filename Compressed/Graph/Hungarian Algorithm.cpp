namespace wm{
bool vis[N]; int U[N],V[N],P[N];
int way[N],minv[N],match[N],ar[N][N];
///n=no of row, m=no of col, 1 based,
///flag=MAXIMIZE/MINIMIZE
///match[i] = the column to which row i is matched
int hungarian(int n,int m,int mat[N][N],int flag){
  clr(U), clr(V), clr(P), clr(ar), clr(way);
  for (int i = 1; i <= n; i++){
    for (int j = 1; j <= m; j++){
      ar[i][j] = mat[i][j];
      if (flag == MAXIMIZE) ar[i][j] = -ar[i][j];
    }
  }
  if (n > m) m = n;
  int i, j, a, b, c, d, r, w;
  for (i = 1; i <= n; i++){
    P[0] = i, b = 0;
    for (j=0; j<=m; j++) minv[j]=inf, vis[j] = 0;
    do{
      vis[b] = true; a = P[b], d = 0, w = inf;
      for (j = 1; j <= m; j++){
        if (!vis[j]){
          r = ar[a][j] - U[a] - V[j];
          if (r < minv[j]) minv[j] = r, way[j]=b;
          if (minv[j] < w) w = minv[j], d = j;
        }
      }
      for (j = 0; j <= m; j++){
        if (vis[j]) U[P[j]] += w, V[j] -= w;
        else minv[j] -= w;
      }
      b = d;
    } while (P[b] != 0);
    do{
      d = way[b]; P[b] = P[d], b = d;
    } while (b != 0);
  }
  for (j = 1; j <= m; j++) match[P[j]] = j;
  return (flag == MINIMIZE) ? -V[0] : V[0];
}
}
