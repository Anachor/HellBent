void FWHT(vector<LL> &p, bool inv) {
  int n = p.size(); assert((n&(n-1))==0);
  for (int len=1; 2*len<=n; len <<= 1) {
    for (int i = 0; i < n; i += len+len){
      for (int j = 0; j < len; j++) {
        LL u = p[i+j], v = p[i+len+j];
///XOR  p[i+j]=u+v; p[i+len+j]=u-v;
///OR   if(!inv) p[i+j]=v,p[i+len+j]=u+v;
///OR   else p[i+j] = -u+v,p[i+len+j]=u;
///AND  if(!inv) p[i+j]=u+v,p[i+len+j]=u;
///AND  else p[i+j]=v, p[i+len+j]=u-v;
          }
      }
  }
///XOR if(inv)for(int i=0;i<n;i++)p[i]/=n;
}
