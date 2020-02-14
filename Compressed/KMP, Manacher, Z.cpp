vector<int> prefix_function (string s) {
  int n = s.length(); vector<int> pi(n);
  for (int i=1; i<n; ++i) {
  int j = pi[i-1];
  while(j>0 && s[i] != s[j]) j=pi[j-1];
    if (s[i] == s[j])  ++j;
    pi[i] = j;
  }
  return pi;
}
vector<int> z_function(string s) {
  int n=s.size(),l=0,r=0;vector<int>z(n);
  for (int i=1; i<n; i++) {
    if (i<=r) z[i] = min(r-i+1, z[i-l]);
    while(i+z[i]<n && s[i+z[i]]==s[z[i]])
      z[i]++;
    if (i+z[i]-1>r) l = i, r = i+z[i]-1;
  }
  return z;
}
//0-based indexing
//p[0][i]:mxlen of hlfpal arnd hlf idx i
//p[1][i]:mxlen of hlfpal arnd idx i
VI p[2];
void manacher(const string s) {
  int n=s.size();p[0]=VI(n+1);p[1]=VI(n);
  for (int z=0; z<2; z++)
    for (int i=0, l=0, r=0; i<n; i++) {
      int t = r - i + !z;
      if (i<r) p[z][i]=min(t, p[z][l+t]);
      int L=i-p[z][i], R=i+p[z][i]-!z;
      while(L>=1&&R+1<n&&s[L-1]==s[R+1])
        p[z][i]++, L--, R++;
      if (R>r) l=L, r=R;
    }
}
bool ispalin(int l, int r) {
  int mid=(l+r+1)/2, sz = r-l+1;
  return 2*p[sz%2][mid]+(sz%2) >= sz;
}
