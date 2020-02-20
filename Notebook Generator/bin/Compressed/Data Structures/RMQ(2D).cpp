int st[K][K][N][N]; int lg[N];
void pre() {
  lg[1] = 0;
  for (int i=2; i<N; i++) lg[i] = lg[i/2]+1;
}
int query(int l1, int r1, int l2, int r2) {
  int xx = lg[l2-l1+1], yy = lg[r2-r1+1];
  return max(max(st[xx][yy][l1][r1],
             st[xx][yy][l2-(1<<xx)+1][r1]),
         max(st[xx][yy][l1][r2-(1<<yy)+1],
         st[xx][yy][l2-(1<<xx)+1][r2-(1<<yy)+1]));
}
void build() {
  for (int x=0; x<K; x++) {
    for (int y=0; y<K; y++) {
      for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
          if (i+(1<<x)-1>n || j+(1<<y)-1>m)
            continue;
          if (!x&&!y) st[0][0][i][j]=flag[i][j];
          else if (x>0) st[x][y][i][j] =
max(st[x-1][y][i][j],st[x-1][y][i+(1<<(x-1))][j]);
          else if (y>0) st[x][y][i][j] =
max(st[x][y-1][i][j],st[x][y-1][i][j+(1<<(y-1))]);
        }
      }
    }
  }
}
