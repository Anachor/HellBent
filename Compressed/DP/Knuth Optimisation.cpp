//There are n points on the segment (0, l). You
//have to mark the points in some order. Cost of
//picking a point. Cost of marking is the distance
//between closest marked points to the left and
//to the right. Minimise cost.
LL a[N], dp[N][N], opt[N][N];
LL Knuth(int l, int n) {
  a[0] = 0; a[++n] = l;
  for (int i=1;i<=n;i++) opt[i-1][i]=i-1;
  for (int len=2; len<=n; len++)
    for (int l=0; l+len<=n; l++) {
      int r = l+len, optl = opt[l][r-1];
      int optr = opt[l+1][r]; dp[l][r] = INF;
      for (int i=optl; i<=optr; i++) {
        LL c = dp[l][i] + dp[i][r] + a[r] - a[l];
        if(c<dp[l][r])  dp[l][r] = c, opt[l][r]=i;
      }
    }
    return dp[0][n];
}
