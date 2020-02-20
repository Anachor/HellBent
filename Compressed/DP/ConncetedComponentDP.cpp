i64 f(int n,int r,int k,int c,int st,int en) {
  if(n==0||c<0||st<0||en <0) return 0 ;
  r = (r+a[n]*(2*c+st+en))%M ;
  if(dp[n][r][k][c][st][en]!=-1)
    return dp[n][r][k][c][st][en];
  i64 ans = f(n-1,r,k,c,st,en);/*it is not used*/
  if(k==1) {
    if( c==0 && (st||en) && r==0 ) ans++;
    /* if this is the last element to take
    then is should either connect st and en ,
    or be the first element or last */
  }
  else{
    if(st==0) ans+=(f(n-1,r,k-1,c,1,en)+f(n-1,r,
    k-1,c-1,1,en)*c); // this is starting element
    if(en==0) ans += ( f(n-1,r,k-1,c,st,1) +
f(n-1,r,k-1,c-1,st,1)*c);// this is ending element
    ans += f( n-1 , r , k-1 , c+1 , st , en );
    // created & independent
    ans += f(n-1,r,k-1,c,st,en)*2*c+
    f(n-1,r,k-1,c,st,en)*(st+en);
    /*created and connected with some other
    component possibly start or end component */
    ans += (f(n-1,r,k-1,c-1,st,en)*c*(c-1)+
            f(n-1,r,k-1,c-1,st,en)*c*(st+en));
/*created and connected between two component */
  }
  return dp[n][r][k][c][st][en] = ans%mod;
}
