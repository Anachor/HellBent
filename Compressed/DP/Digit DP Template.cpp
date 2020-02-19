int call(int pos, int st, int sm,
         bool strt, bool alLarge, bool alSmall) {
  if(sm > limit) return 0;
  if(pos == 200) return 1;
  if(dp[pos][st][sm][strt][alLarge][alSmall]!=-1)
    return dp[pos][st][sm][strt][alLarge][alSmall];
  int ret = 0;
  for(int i = 0; i < base; i++) {
    if(alLarge == false && i<L[pos]-'a') continue;
    if(alSmall == false && i>R[pos]-'a') continue;
    int npos = pos + 1;
    bool nstrt = strt|(i>0);
    bool nalLarge = alLarge|(i>L[pos]-'a');
    bool nalSmall = alSmall|(i<R[pos]-'a');
    int nst = st;
    if(nstrt) nst = Next(nst, 'a' + i);
    int nsm = sm + sts[nst].cnt;
    add(ret,
      call(npos,nst,nsm,nstrt,nalLarge,nalSmall));
  }
  dp[pos][st][sm][strt][alLarge][alSmall] = ret;
  return ret;
}
