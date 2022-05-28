//Batch Scheduling
int dp[maxn],t[maxn],f[maxn],n,s;
int w(int i,int x){
  return(t[x]-t[i]+s)*(f[n]-f[i]);
}
int main(){
  scanf("%d %d",&n,&s) ;
  for(int i=1 ; i<=n ; i++){
    scanf("%d %d",&t[i],&f[i]) ;
    t[i] += t[i-1] ; f[i] += f[i-1] ;
  }
  vector < pair<int,int> > vp ; // pos , best-k
  vp.pb( mp( 0 , 0 ) ) ;
  for(int x=1 ; x<=n ; x++){
    int idx=upper_bound(vp.begin(),
                vp.end(),mp(x,n+1)) - vp.begin() ;
    idx-- ;
    dp[x]=dp[vp[idx].yy]+w(vp[idx].yy,x);
    while( (int)vp.size() > 0 ){
      if(vp.back().xx>x&&dp[x]+w(x,vp.back().xx)<=
        dp[vp.back().yy]+w(vp.back().yy,
                vp.back().xx))vp.pop_back();
      else break ;
    }
    if(vp.size()==0) vp.push_back(mp(0,x));
    else{
      int lo = max(vp.back().xx,x+1),hi=n;
      if(lo>hi||dp[vp.back().yy]+
        w(vp.back().yy,hi)<=dp[x]+w(x,hi))continue;
      while( lo < hi ){
        int mid = (lo+hi)/2 ;
        if( dp[vp.back().yy]+w(vp.back().yy,mid)<=
           dp[x]+w(x,mid))lo=mid+1;
        else hi=mid;
      }
      vp.pb( mp( lo , x ) ) ;
    }
  }
  printf("%d\n",dp[n]);
}
